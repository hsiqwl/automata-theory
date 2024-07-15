#ifndef INTERPRETER_AST_H
#define INTERPRETER_AST_H
#include "node_traits.h"
#include "node.h"

class NodeVisitor;

class Ast{
private:
    Node* root_ = nullptr;

public:
    Ast() = default;

    Ast(Node&& node);

    Ast(BinaryOpKind bin_op_kind, Ast&& lhs, Ast&& rhs);

    Ast(UnaryOpKind un_op_kind, Ast&& operand);

    void AcceptVisitor(NodeVisitor& visitor);
};

#endif //INTERPRETER_AST_H
