#include "node_traits.h"
#include "printer.h"

void AstPrinter::Visit(const UnaryOpNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const BinaryOpNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const IdentifierNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(const NumericLiteralNode &node) {
    node.PrintOut(*buf_);
}