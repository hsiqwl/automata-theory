#include "type_resolver.h"
#include "node_traits.h"

TypeResolver::TypeResolver(SymbolTableManager *manager): SharableObjectHolder<SymbolTableManager>(manager) {}

void TypeResolver::Visit(const VarDeclNode &node) {
    Return(node.GetType());
}

void TypeResolver::Visit(const SignedLiteralNode &node) {
    Return(TypeHolderWrapper{TypeHolder{TypeToken::Signed}});
}

void TypeResolver::Visit(const UnsignedLiteralNode &node) {
    Return(TypeHolderWrapper{TypeHolder{TypeToken::Unsigned}});
}

void TypeResolver::Visit(const VarReferenceNode &node) {
    Return(object_ptr_->GetVar(node.GetVarName()).GetType());
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
    if (left_type.index() == 1) {
        Return(std::move(left_type));
        return;
    }
    auto right_type = GetValue(node.GetRight().get(), object_ptr_);
    if (right_type.index() == 1) {
        Return(std::move(right_type));
        return;
    }
    if (!std::get<0>(right_type).IsConvertibleTo(std::get<0>(left_type))) {
        Return(std::make_shared<NoKnownConversion>());
        return;
    }
    Return(std::move(left_type));
}

void TypeResolver::Visit(const StatementListNode &node) {
    Return(GetValue(node[node.NumOfStatements() - 1].get(), object_ptr_));
}

void TypeResolver::Visit(const UnaryOpNode &node) {
    Return(GetValue(node.GetOperand().get(), object_ptr_));
}

void TypeResolver::Visit(const IfNode &node) {
    Return({});
}

void TypeResolver::Visit(const WhileNode &node) {
    Return({});
}

void TypeResolver::Visit(const FuncCallNode &node) {
    Return(object_ptr_->GetFunc(node.GetFuncName()).GetReturnType());
}

void TypeResolver::Visit(const FuncDeclNode &node) {
    Return(TypeHolderWrapper{});
}