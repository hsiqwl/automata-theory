#include "ast_printer.h"

void AstPrinter::print(Ast& tree, std::ostream& stream) {
    for (auto iter = tree.begin(), end = tree.end(); iter != end; ++iter) {
        INode &node = **iter;
        Visit(Overload{
                [&stream](BinaryOpNode &node) -> void { node.PrintOut(stream); },
                [&stream](UnaryOpNode &node) -> void { node.PrintOut(stream); },
                [&stream](IdentifierNode &node) -> void { node.PrintOut(stream); },
                [&stream](NumericLiteralNode &node) -> void { node.PrintOut(stream); }
                }, node);
    }
}