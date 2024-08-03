#include "semantic_analyzer.h"
#include "node_traits.h"

SemanticAnalyzer::SemanticAnalyzer(SymbolTableManager *manager): SharableObjectHolder<SymbolTableManager>(manager) {}

VarSymbol SemanticAnalyzer::CreateVarSymbol(const VarDeclNode &node) {
    return {node.GetName(), node.GetType(), node.IsConst()};
}

FunctionSymbol SemanticAnalyzer::CreateFuncSymbol(const FuncDeclNode &node, SymbolTableManager &manager) {
    std::vector<VarSymbol> params;
    for (const auto &param: node.GetFuncParams())
        params.emplace_back(CreateVarSymbol(*param));
    auto return_type = std::get<0>(TypeResolver::GetValue(node.GetFuncBody().get(), &manager));
    return {node.GetFuncName(), return_type, std::move(params)};
}

void SemanticAnalyzer::Visit(const AssignNode &node) {
    SemanticErrorContext context;
    context.Add(GetValue(node.GetLeft().get(), object_ptr_));
    context.Add(GetValue(node.GetRight().get(), object_ptr_));
    if (context.IsEmpty())
        ChecksPerformer<AssignNode>::PerformChecks(node, *object_ptr_, context);
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const VarDeclNode &node) {
    SemanticErrorContext context;
    ChecksPerformer<VarDeclNode>::PerformChecks(node, *object_ptr_, context);
    if(context.IsEmpty()) {
        auto var_sym = std::make_unique<VarSymbol>(CreateVarSymbol(node));
        object_ptr_->InsertSymbol(std::move(*var_sym));
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const VarReferenceNode &node) {
    SemanticErrorContext context;
    ChecksPerformer<VarReferenceNode>::PerformChecks(node, *object_ptr_, context);
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
    ChecksPerformer<InitializationNode>::PerformChecks(node, *object_ptr_, context);
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
    context.Add(GetValue(node.GetLeft().get(), object_ptr_));
    if(context.IsEmpty())
        context.Add(GetValue(node.GetRight().get(), object_ptr_));
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const UnaryOpNode &node) {
    Return(GetValue(node.GetOperand().get(), object_ptr_));
}

void SemanticAnalyzer::Visit(const IfNode &node) {
    SemanticErrorContext context;
    ChecksPerformer<IfNode>::PerformChecks(node, *object_ptr_, context);
    if (context.IsEmpty()) {
        object_ptr_->AddNewScope("IF_CLAUSE of " + object_ptr_->GetCurrentScopeName(),
                                 object_ptr_->GetCurrentScopeLevel() + 1);
        context.Add(GetValue(node.GetBody().get(), object_ptr_));
        object_ptr_->RemoveCurrentScope();
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const WhileNode &node) {
    SemanticErrorContext context;
    ChecksPerformer<WhileNode>::PerformChecks(node, *object_ptr_, context);
    if (context.IsEmpty()) {
        object_ptr_->AddNewScope("WHILE_CLAUSE of" + object_ptr_->GetCurrentScopeName(),
                                 object_ptr_->GetCurrentScopeLevel() + 1);
        context.Add(GetValue(node.GetBody().get(), object_ptr_));
        object_ptr_->RemoveCurrentScope();
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const FuncDeclNode &node) {
    SemanticErrorContext context;
    ChecksPerformer<FuncDeclNode>::PerformChecks(node, *object_ptr_, context);
    if (context.IsEmpty()) {
        object_ptr_->AddNewScope(node.GetFuncName(), object_ptr_->GetCurrentScopeLevel() + 1);
        for (auto &param: node.GetFuncParams())
            context.Add(GetValue(param.get(), object_ptr_));
        if (context.IsEmpty())
            context.Add(GetValue(node.GetFuncBody().get(), object_ptr_));
        std::unique_ptr<FunctionSymbol> func_symbol;
        if (context.IsEmpty())
            func_symbol = std::make_unique<FunctionSymbol>(CreateFuncSymbol(node, *object_ptr_));
        object_ptr_->RemoveCurrentScope();
        if (func_symbol != nullptr)
            object_ptr_->InsertSymbol(std::move(*func_symbol));
    }
    Return(std::move(context));
}

void SemanticAnalyzer::Visit(const FuncCallNode &node) {
    SemanticErrorContext context;
    ChecksPerformer<FuncCallNode>::PerformChecks(node, *object_ptr_, context);
    Return(std::move(context));
}

