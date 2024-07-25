#ifndef INTERPRETER_AST_H
#define INTERPRETER_AST_H
#include "node_traits.h"
#include <iostream>

class Ast{
private:
    std::unique_ptr<INode> root_;

public:
    Ast() = default;

    Ast(std::unique_ptr<INode>&& node);

    void PrintOut(std::ostream& stream = std::cout) const;

    long Evaluate() const;
};

#endif //INTERPRETER_AST_H
