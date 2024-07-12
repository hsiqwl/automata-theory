#ifndef INTERPRETER_AST_PRINTER_H
#define INTERPRETER_AST_PRINTER_H
#include "ast.h"
#include <iostream>

class AstPrinter{
public:
    static void print(Ast& tree, std::ostream& stream = std::cout);

private:
};

#endif //INTERPRETER_AST_PRINTER_H
