#ifndef INTERPRETER_AST_BUILDER_H
#define INTERPRETER_AST_BUILDER_H
#include "ast.h"

class ast_builder{
private:
    ast tree;

public:
    ast_builder() = default;

    void build_operand(std::unique_ptr<Node>&& operand);

    void build_operation(std::unique_ptr<Node>&& operation);

    ast get_tree() const;
};


#endif //INTERPRETER_AST_BUILDER_H
