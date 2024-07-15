#include "node_traits.h"
#include "printer.h"

void AstPrinter::Visit(UnaryOpNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(BinaryOpNode &node) {

    node.PrintOut(*buf_);
}

void AstPrinter::Visit(IdentifierNode &node) {
    node.PrintOut(*buf_);
}

void AstPrinter::Visit(NumericLiteralNode &node) {
    node.PrintOut(*buf_);
}