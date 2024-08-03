#ifndef INTERPRETER_SEMANTIC_ANALYZER_H
#define INTERPRETER_SEMANTIC_ANALYZER_H
#include "check_performer.h"

class SemanticAnalyzer: public SharableObjectHolder<SymbolTableManager>,
                        public ValueGetterWithSharableObjectHolder
                        <
                        SemanticAnalyzer,
                        INode*,
                        SemanticErrorContext
                        >,
                        public NodeVisitor{
public:
    SemanticAnalyzer(SymbolTableManager* manager);

    void Visit(const BinaryOpNode& node) override;

    void Visit(const UnaryOpNode& node) override;

    void Visit(const VarDeclNode& node) override;

    void Visit(const VarReferenceNode& node) override;

    void Visit(const AssignNode& node) override;

    void Visit(const StatementListNode& node) override;

    void Visit(const SignedLiteralNode& node) override;

    void Visit(const UnsignedLiteralNode& node) override;

    void Visit(const InitializationNode& node) override;

    void Visit(const IfNode& node) override;

    void Visit(const WhileNode& node) override;

    void Visit(const FuncDeclNode& node) override;

    void Visit(const FuncCallNode& node) override;

private:
    static VarSymbol CreateVarSymbol(const VarDeclNode& node);

    static FunctionSymbol CreateFuncSymbol(const FuncDeclNode& node, SymbolTableManager& manager);
};

#endif //INTERPRETER_SEMANTIC_ANALYZER_H
