#ifndef INTERPRETER_SEMANTIC_ANALYZER_H
#define INTERPRETER_SEMANTIC_ANALYZER_H
#include "node_interface.h"
#include "node_visitor.h"
#include "value_getter.h"
#include "semantic_error_context.h"
#include "sym_tab_manager.h"

class SemanticAnalyzer:
        public ValueGetter<SemanticAnalyzer, std::unique_ptr<INode>, SemanticErrorContext>,
        public NodeVisitor{
public:
    void Visit(const BinaryOpNode& node) override;

    void Visit(const UnaryOpNode& node) override;

    void Visit(const VarDeclNode& node) override;

    void Visit(const VarReferenceNode& node) override;

    void Visit(const AssignNode& node) override;

    void Visit(const StatementListNode& node) override;

    void Visit(const SignedLiteralNode& node) override;

    void Visit(const UnsignedLiteralNode& node) override;

    void Visit(const InitializationNode& node) override;

private:
    SymbolTableManager scope_manager_;

};

#endif //INTERPRETER_SEMANTIC_ANALYZER_H
