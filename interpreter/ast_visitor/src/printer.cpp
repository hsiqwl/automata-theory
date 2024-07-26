#include "node_traits.h"
#include "printer.h"

void AstPrinter::Visit(const UnaryOpNode &node) {
    node.GetOperand()->Accept(*this);
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const BinaryOpNode &node) {
    node.GetLeft()->Accept(*this);
    node.GetRight()->Accept(*this);
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const VarDeclNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const VarReferenceNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const AssignNode &node) {
    node.GetLeft()->Accept(*this);
    node.GetRight()->Accept(*this);
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const StatementListNode &node) {
    node.PrintOut(*buf_);
    for (auto stmt_i = 0; stmt_i < node.NumOfStatements(); ++stmt_i) {
        (*buf_) << "PROCESSING NEW STATEMENT\n";
        node[stmt_i]->Accept(*this);
        (*buf_) << "END OF STATEMENT\n";
    }
    (*buf_) << "END OF ALL STATEMENTS\n";
}

void AstPrinter::Visit(const SignedLiteralNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const UnsignedLiteralNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const InitializationNode &node) {
    node.GetVarToInit()->Accept(*this);
    node.GetInitExpr()->Accept(*this);
    node.PrintOut(*buf_);
}