#include "type_resolver.h"
#include "node_traits.h"

TypeResolver::TypeResolver(SymbolTableManager *manager): SharableObjectHolder<SymbolTableManager>(manager) {}

void TypeResolver::Visit(const VarDeclNode &node) {
    auto var_type = node.GetType();
    Return(std::move(var_type));
}

void TypeResolver::Visit(const SignedLiteralNode &node) {
    Return(TypeHolderWrapper{TypeHolder{TypeToken::Signed}});
}

void TypeResolver::Visit(const UnsignedLiteralNode &node) {
    Return(TypeHolderWrapper{TypeHolder{TypeToken::Unsigned}});
}

void TypeResolver::Visit(const VarReferenceNode &node) {
    auto var_type = dynamic_cast<const VarSymbol&>(object_ptr_->GetSymbol(node.GetVarName())).GetType();
    Return(std::move(var_type));
}

void TypeResolver::Visit(const AssignNode &node) {
    Return(GetValue(node.GetLeft().get(), object_ptr_));
}

void TypeResolver::Visit(const InitializationNode &node) {
    auto type = node.GetVarToInit()->GetType();
    Return(std::move(type));
}

void TypeResolver::Visit(const BinaryOpNode &node) {
    auto left_type = GetValue(node.GetLeft().get(), object_ptr_);
    auto right_type = GetValue(node.GetRight().get(), object_ptr_);
    if (left_type.IsSimpleType() &&
        right_type.IsSimpleType() &&
        right_type.IsConvertibleTo(left_type)) {
        Return(std::move(left_type));
    } else {
        throw NoKnownConversion{};
    }
}

void TypeResolver::Visit(const StatementListNode &node) {
    Return(GetValue(node[node.NumOfStatements() - 1].get(), object_ptr_));
}

void TypeResolver::Visit(const UnaryOpNode &node) {
    Return(GetValue(node.GetOperand().get(), object_ptr_));
}