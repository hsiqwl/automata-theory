#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H
#include "node_interface.h"
#include "node_visitor.h"
#include "value_getter.h"
#include <memory>

class Interpreter: public ValueGetter<Interpreter, std::unique_ptr<INode>, long>, public NodeVisitor{
public:
    void Visit(const BinaryOpNode& node) override;

    void Visit(const UnaryOpNode& node) override;

};

#endif //INTERPRETER_INTERPRETER_H
