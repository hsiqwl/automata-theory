#include "ast.h"

Ast::Ast(Node &&node) : root_(new Node{std::move(node)}){}

Ast::Ast(BinaryOpKind bin_op_kind, Ast &&lhs, Ast &&rhs)
    : root_(new Node{BinaryOpNode{bin_op_kind, &**lhs.root_, &**rhs.root_}}) {}

Ast::Ast(UnaryOpKind un_op_kind, Ast &&operand)
    : root_(new Node{UnaryOpNode{un_op_kind, &**operand.root_}}) {}

void Ast::AcceptVisitor(NodeVisitor &visitor) {
    (*root_)->Accept(visitor);
}