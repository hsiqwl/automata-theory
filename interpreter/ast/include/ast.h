#ifndef INTERPRETER_AST_H
#define INTERPRETER_AST_H
#include "node_traits.h"

class Ast{
private:
    std::unique_ptr<INode> root_;

public:
    Ast() = default;

    Ast(std::unique_ptr<INode>&& node);

    const std::unique_ptr<INode>& GetRoot() const noexcept;
};

#endif //INTERPRETER_AST_H
