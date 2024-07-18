#include "node_traits.h"
#include "printer.h"

void AstPrinter::Visit(const UnaryOpNode &node) {
    node.GetOperand()->Accept(*this);
    (*buf_) << "UnaryOpNode:" << node.label_ << '\n';
}

void AstPrinter::Visit(const BinaryOpNode &node) {
    node.GetLeft()->Accept(*this);
    node.GetRight()->Accept(*this);
    (*buf_) << "BinaryOpNode:" << node.label_ << '\n';
}

void AstPrinter::Visit(const NumericLiteralNode &node) {
    (*buf_) << "NumericLiteralNode:" << node.label_ << '\n';
}

void AstPrinter::Visit(const VarDeclNode &node) {
    (*buf_) << "VarDeclNode:" << node.label_ << '\n';
}

void AstPrinter::Visit(const VarReferenceNode &node) {
    (*buf_) << "VarReferenceNode:" << node.label_ << '\n';
}