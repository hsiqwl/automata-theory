#ifndef INTERPRETER_PRINTER_H
#define INTERPRETER_PRINTER_H
#include "node_visitor.h"
#include <fstream>
#include <iostream>

class AstPrinter: public NodeVisitor{
public:
    void Visit(const BinaryOpNode& node) override;

    void Visit(const UnaryOpNode& node) override;

    void Visit(const IdentifierNode& node) override;

    void Visit(const NumericLiteralNode& node) override;

    std::ostream* buf_ = &std::cout;
};

#endif //INTERPRETER_PRINTER_H
