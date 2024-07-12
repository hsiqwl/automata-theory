#include "ast_printer.h"

void AstPrinter::print(Ast& tree, std::ostream& stream) {
    for (auto & node : tree) {
        node->PrintOut(stream);
    }
}