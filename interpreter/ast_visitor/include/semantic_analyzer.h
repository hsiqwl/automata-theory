#ifndef INTERPRETER_SEMANTIC_ANALYZER_H
#define INTERPRETER_SEMANTIC_ANALYZER_H
#include "type_resolver.h"
#include "semantic_error_context.h"

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
    bool CorrectNumberOfArguments(const FuncCallNode& node, const FunctionSymbol& symbol);

    bool ArgumentsAreOfCorrectType(const FuncCallNode& node, const FunctionSymbol& symbol);
};

#endif //INTERPRETER_SEMANTIC_ANALYZER_H
