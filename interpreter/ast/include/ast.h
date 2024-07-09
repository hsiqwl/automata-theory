#ifndef INTERPRETER_AST_H
#define INTERPRETER_AST_H
#include "operand_node.h"
#include "operation_node.h"
#include <memory>

class ast_builder;

class ast{
private:
    std::shared_ptr<node> root;

    friend class ast_builder;

public:
    ast() = default;

    ast(std::shared_ptr<node>&& root);
};

#endif //INTERPRETER_AST_H
