#ifndef INTERPRETER_PRINTER_H
#define INTERPRETER_PRINTER_H
#include "node_visitor.h"
#include <fstream>
#include <iostream>

class AstPrinter: public NodeVisitor{
public:
    void Visit(BinaryOpNode& node) override;

    void Visit(UnaryOpNode& node) override;

    void Visit(IdentifierNode& node) override;

    void Visit(NumericLiteralNode& node) override;

    std::ostream* buf_ = &std::cout;
};

#endif //INTERPRETER_PRINTER_H
