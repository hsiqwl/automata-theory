#include "semantic_analyzer.h"
#include "node_traits.h"

SemanticAnalyzer::SemanticAnalyzer(SymbolTableManager *manager): SharableObjectHolder<SymbolTableManager>(manager) {}

void SemanticAnalyzer::Visit(const AssignNode &node) {
    SemanticErrorContext context;
    context.Add(GetValue(node.GetLeft().get(), object_ptr_));
    context.Add(GetValue(node.GetRight().get(), object_ptr_));
    try {
        auto lhs_type = TypeResolver::GetValue(node.GetLeft().get(), object_ptr_);
        auto rhs_type = TypeResolver::GetValue(node.GetRight().get(), object_ptr_);
        if (lhs_type.IsConst())
            context.Add(std::make_unique<AssignmentOfConstVar>());
        if (!rhs_type.IsConvertibleTo(lhs_type))
            context.Add(std::make_unique<NoKnownConversion>());
    } catch (const SemanticError &error) {
        context.Add(std::make_unique<NoKnownConversion>());
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const VarDeclNode &node) {
    SemanticErrorContext context;
    if (object_ptr_->SymbolDeclaredInCurrentScope(node.GetName())) {
        auto *p_var = dynamic_cast<const VarSymbol *>(&object_ptr_->GetSymbol(node.GetName()));
        if (p_var != nullptr) {
            if (node.GetType().IsSameAs(p_var->GetType())) {
                context.Add(std::make_unique<RedeclarationOfIdentifier>());
            } else {
                context.Add(std::make_unique<ConflictingDeclaration>());
            }
        }
    } else {
        auto var = std::make_unique<VarSymbol>(node.GetName(), node.GetType(), node.IsConst());
        object_ptr_->InsertSymbolToCurrentScope(std::move(var));
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const VarReferenceNode &node) {
    SemanticErrorContext context;
    if (!object_ptr_->SymbolDeclaredSomewhere(node.GetVarName())) {
        context.Add(std::make_unique<UseOfUndeclaredIdentifier>());
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const SignedLiteralNode &node) {
    Return(SemanticErrorContext{});
}

void SemanticAnalyzer::Visit(const UnsignedLiteralNode &node) {
    Return(SemanticErrorContext{});
}

void SemanticAnalyzer::Visit(const InitializationNode &node) {
    SemanticErrorContext context;
    context.Add(GetValue(node.GetVarToInit().get(), object_ptr_));
    if(node.GetInitExpr() != nullptr)
        context.Add(GetValue(node.GetInitExpr().get(), object_ptr_));
    try {
        if (node.GetInitExpr() != nullptr) {
            auto lhs_type = TypeResolver::GetValue(node.GetVarToInit().get(), object_ptr_);
            auto rhs_type = TypeResolver::GetValue(node.GetInitExpr().get(), object_ptr_);
            if (!lhs_type.IsConvertibleTo(rhs_type)) {
                context.Add(std::make_unique<NoKnownConversion>());
            }
        }
    } catch (const SemanticError &error) {
        context.Add(std::make_unique<NoKnownConversion>());
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const StatementListNode &node) {
    SemanticErrorContext context;
    for(size_t i = 0; i < node.NumOfStatements(); ++i){
        context.Add(GetValue(node[i].get(), object_ptr_));
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const BinaryOpNode &node) {
    SemanticErrorContext context;
    try {
        context.Add(GetValue(node.GetLeft().get(), object_ptr_));
        context.Add(GetValue(node.GetLeft().get(), object_ptr_));
        auto lhs_type = TypeResolver::GetValue(node.GetLeft().get(), object_ptr_);
        auto rhs_type = TypeResolver::GetValue(node.GetRight().get(), object_ptr_);
        if (!lhs_type.IsConvertibleTo(rhs_type)) {
            context.Add(std::make_unique<NoKnownConversion>());
        }
    } catch (const SemanticError &error) {
        context.Add(std::make_unique<NoKnownConversion>());
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const UnaryOpNode &node) {
    Return(SemanticErrorContext{});
}

void SemanticAnalyzer::Visit(const IfNode &node) {
    SemanticErrorContext context;
    auto acceptable_predicate_type = TypeHolderWrapper{TypeHolder{TypeToken::Signed}};
    auto actual_predicate_type = TypeResolver::GetValue(node.GetPredicate().get(), object_ptr_);
    if (actual_predicate_type.IsConvertibleTo(acceptable_predicate_type)) {
        object_ptr_->AddNewScope("if-clause of" + object_ptr_->GetCurrentScopeName(),
                                 object_ptr_->GetCurrentScopeLevel() + 1);
        context.Add(GetValue(node.GetBody().get(), object_ptr_));
    } else {
        context.Add(std::make_unique<NoKnownConversion>());
    }
    object_ptr_->RemoveCurrentScope();
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const WhileNode &node) {
    SemanticErrorContext context;
    auto acceptable_predicate_type = TypeHolderWrapper{TypeHolder{TypeToken::Signed}};
    auto actual_predicate_type = TypeResolver::GetValue(node.GetPredicate().get(), object_ptr_);
    if (actual_predicate_type.IsConvertibleTo(acceptable_predicate_type)) {
        object_ptr_->AddNewScope("while-clause of" + object_ptr_->GetCurrentScopeName(),
                                 object_ptr_->GetCurrentScopeLevel() + 1);
        context.Add(GetValue(node.GetBody().get(), object_ptr_));
    } else {
        context.Add(std::make_unique<NoKnownConversion>());
    }
    object_ptr_->RemoveCurrentScope();
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const FuncDecl &node) {
    SemanticErrorContext context;
    object_ptr_->AddNewScope(node.GetFuncName(), object_ptr_->GetCurrentScopeLevel() + 1);
    for (const auto &param: node.GetFuncParams()) {
        context.Add(GetValue(param.get(), object_ptr_));
    }
    context.Add(GetValue(node.GetFuncBody().get(), object_ptr_));
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const FuncCall &node) {
    SemanticErrorContext context;
    bool symbol_declared = object_ptr_->SymbolDeclaredSomewhere(node.GetFuncName());
    auto *p_fun = dynamic_cast<const FunctionSymbol *>(&object_ptr_->GetSymbol(node.GetFuncName()));
    if (symbol_declared && (p_fun != nullptr)) {
        if (CorrectNumberOfArguments(node, *p_fun)) {
            if (!ArgumentsAreOfCorrectType(node, *p_fun))
                context.Add(std::make_unique<ArgumentsOfIncorrectType>());
        } else {
            context.Add(std::make_unique<IncorrectNumberOfArguments>());
        }
    } else {
        context.Add(std::make_unique<CallToUndeclaredFunction>());
    }
}

bool SemanticAnalyzer::CorrectNumberOfArguments(const FuncCall &node, const FunctionSymbol &symbol) {
    return node.GetArgs().size() == symbol.GetParamNumber();
}

bool SemanticAnalyzer::ArgumentsAreOfCorrectType(const FuncCall &node, const FunctionSymbol &symbol) {
    bool result = true;
    try {
        const auto &args = node.GetArgs();
        for (size_t i = 0; i < args.size(); ++i) {
            auto &param = symbol.GetParamByIndex(i);
            result = result && TypeResolver::GetValue(args[i].get(), object_ptr_).IsConvertibleTo(param.GetType());
        }
    } catch (...) {
        result = false;
    }
    return result;
}