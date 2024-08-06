#ifndef INTERPRETER_SEMANTIC_ANALYZER_HELPERS_H
#define INTERPRETER_SEMANTIC_ANALYZER_HELPERS_H
#include "type_resolver.h"
#include "semantic_error_context.h"
#include "node_traits.h"

template <typename NodeType>
class ChecksPerformer{
public:
    static void PerformChecks(const NodeType& node, SymbolTableManager& manager, SemanticErrorContext& context) { static_assert(false, "Cannot instantiate checker for unknown type of node");}
};

template<>
class ChecksPerformer<VarDeclNode> {
public:
    static void PerformChecks(const VarDeclNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        if (manager.VarDeclaredInCurrentScope(node.GetName())) {
            auto &var = manager.GetVar(node.GetName());
            if (var.GetType().IsSameAs(node.GetType()))
                context.Add(std::make_shared<RedeclarationOfIdentifier>(node.GetLocation(), node.GetName()));
            else
                context.Add(std::make_shared<ConflictingDeclaration>(node.GetLocation(), node.GetName()));
        }
    }
};


template <>
class ChecksPerformer<FuncDeclNode> {
public:
    static void PerformChecks(const FuncDeclNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        if (manager.FuncDeclared(node.GetFuncName()))
            context.Add(std::make_shared<RedeclarationOfIdentifier>(node.GetLocation(), node.GetFuncName()));
    }
};

template <>
class ChecksPerformer<FuncCallNode> {
public:
    static void PerformChecks(const FuncCallNode &node, SymbolTableManager &manager, SemanticErrorContext &context) {
        if (!manager.FuncDeclared(node.GetFuncName())) {
            context.Add(std::make_shared<CallToUndeclaredFunction>(node.GetLocation(), node.GetFuncName()));
        } else if (!CorrectNumberOfArguments(node, manager.GetFunc(node.GetFuncName()))) {
            context.Add(std::make_shared<IncorrectNumberOfArguments>(node.GetLocation(), node.GetFuncName(),
                                                                     manager.GetFunc(
                                                                             node.GetFuncName()).GetParamNumber(),
                                                                     node.GetArgs().size()));
        } else {
            auto &func_symbol = manager.GetFunc(node.GetFuncName());
            for (auto iter = node.GetArgs().begin(), end = node.GetArgs().end(); iter != end; ++iter) {
                auto arg_type = TypeResolver::GetValue(iter->get(), &manager);
                auto &param_type = func_symbol.GetParamByIndex(std::distance(node.GetArgs().begin(), iter)).GetType();
                if (arg_type.index() == 1 || !std::get<0>(arg_type).IsConvertibleTo(param_type)) {
                    context.Add(std::make_shared<ArgumentsOfIncorrectType>(node.GetLocation(), node.GetFuncName(),
                                                                           param_type, std::get<0>(arg_type)));
                    return;
                }
            }
        }
    }

private:
    static bool CorrectNumberOfArguments(const FuncCallNode &node, const FunctionSymbol &symbol) {
        return node.GetArgs().size() == symbol.GetParamNumber();
    }
};

template<>
class ChecksPerformer<AssignNode> {
public:
    static void PerformChecks(const AssignNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        auto lhs_type = TypeResolver::GetValue(node.GetLeft().get(), &manager);
        if (lhs_type.index() == 1) {
            context.Add(std::move(std::get<1>(lhs_type)));
            return;
        }
        auto rhs_type = TypeResolver::GetValue(node.GetRight().get(), &manager);
        if (rhs_type.index() == 1) {
            context.Add(std::move(std::get<1>(rhs_type)));
            return;
        }
        if (std::get<0>(lhs_type).IsConst()) {
            context.Add(std::make_shared<AssignmentOfConstVar>(node.GetLocation()));
            return;
        }
        if (!std::get<0>(rhs_type).IsConvertibleTo(std::get<0>(lhs_type))) {
            context.Add(std::make_shared<NoKnownConversion>(node.GetLocation(), std::get<0>(rhs_type), std::get<0>(lhs_type)));
            return;
        }
    }
};

template<>
class ChecksPerformer<VarReferenceNode> {
public:
    static void PerformChecks(const VarReferenceNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        bool var_declared = manager.VarDeclaredInSomeScope(node.GetVarName());
        bool func_declared = manager.FuncDeclared(node.GetVarName());
        if (!(var_declared || func_declared)) {
            context.Add(std::make_shared<UseOfUndeclaredIdentifier>(node.GetLocation(), node.GetVarName()));
        } else if (!var_declared) {
            context.Add(std::make_shared<InvalidIdentifierUsage>(node.GetLocation(), node.GetVarName()));
        }
    }
};

template <>
class ChecksPerformer<InitializationNode> {
public:
    static void PerformChecks(const InitializationNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        auto lhs_type = TypeResolver::GetValue(node.GetVarToInit().get(), &manager);
        if (lhs_type.index() == 1) {
            context.Add(std::move(std::get<1>(lhs_type)));
            return;
        }
        auto &lhs_type_wrapper = std::get<0>(lhs_type);
        if (lhs_type_wrapper.IsConst() && node.GetInitExpr() == nullptr) {
            context.Add(std::make_shared<UninitializedConstVariable>(node.GetLocation(), node.GetVarToInit()->GetName()));
            return;
        }
        if (node.GetInitExpr() != nullptr) {
            auto rhs_type = TypeResolver::GetValue(node.GetInitExpr().get(), &manager);
            if (rhs_type.index() == 1) {
                context.Add(std::move(std::get<1>(rhs_type)));
                return;
            }
            if (!std::get<0>(rhs_type).IsConvertibleTo(lhs_type_wrapper))
                context.Add(std::make_shared<NoKnownConversion>(node.GetLocation(), std::get<0>(rhs_type), lhs_type_wrapper));
        }
    }
};

/*template<>
class ChecksPerformer<UnaryOpNode> {
public:
    static void PerformChecks(const UnaryOpNode& node, SymbolTableManager& manager, SemanticErrorContext& context);
};

template<>
class ChecksPerformer<BinaryOpNode> {
public:
    static void PerformChecks(const BinaryOpNode& node, SymbolTableManager& manager, SemanticErrorContext& context);
};*/

template<>
class ChecksPerformer<IfNode> {
public:
    static void PerformChecks(const IfNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        auto acceptable_predicate_type = TypeHolderWrapper{TypeToken::Signed};
        auto actual_predicate_type = TypeResolver::GetValue(node.GetBody().get(), &manager);
        if (actual_predicate_type.index() == 1) {
            context.Add(std::move(std::get<1>(actual_predicate_type)));
            return;
        }
        if (!std::get<0>(actual_predicate_type).IsConvertibleTo(acceptable_predicate_type))
            context.Add(std::make_shared<NoKnownConversion>(node.GetLocation(), std::get<0>(actual_predicate_type), acceptable_predicate_type));
    }
};

template<>
class ChecksPerformer<WhileNode> {
public:
    static void PerformChecks(const WhileNode& node, SymbolTableManager& manager, SemanticErrorContext& context) {
        auto acceptable_predicate_type = TypeHolderWrapper{TypeToken::Signed};
        auto actual_predicate_type = TypeResolver::GetValue(node.GetBody().get(), &manager);
        if (actual_predicate_type.index() == 1) {
            context.Add(std::move(std::get<1>(actual_predicate_type)));
            return;
        }
        if (!std::get<0>(actual_predicate_type).IsConvertibleTo(acceptable_predicate_type))
            context.Add(std::make_shared<NoKnownConversion>(node.GetLocation(), std::get<0>(actual_predicate_type), acceptable_predicate_type));
    }
};



#endif //INTERPRETER_SEMANTIC_ANALYZER_HELPERS_H
