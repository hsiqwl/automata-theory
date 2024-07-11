#include "ast.h"

Ast::iterator Ast::begin() noexcept {
    return {tree_.begin()};
}

Ast::iterator Ast::end() noexcept {
    return {tree_.end()};
}

Ast::const_iterator Ast::cbegin() const noexcept {
    return {tree_.cbegin()};
}

Ast::const_iterator Ast::cend() const noexcept {
    return {tree_.cend()};
}

Ast::Ast(Node &&node) {
    tree_.emplace_back(std::move(node));
}

Ast::const_iterator Ast::begin() const noexcept {
    return const_iterator{tree_.cbegin()};
}

Ast::const_iterator Ast::end() const noexcept {
    return const_iterator{tree_.cend()};
}

Ast::Ast(BinaryOpKind bin_op_kind, Ast &&lhs, Ast &&rhs) {
    INode *left_operand = &**--lhs.tree_.end();
    INode *right_operand = &**--rhs.tree_.end();
    lhs.tree_.splice(lhs.tree_.end(), std::move(rhs.tree_));
    tree_ = std::move(lhs.tree_);
    tree_.emplace_back(BinaryOpNode(bin_op_kind, left_operand, right_operand));
}

Ast::Ast(UnaryOpKind un_op_kind, Ast &&operand) {
    tree_.splice(tree_.end(), std::move(operand.tree_));
    tree_.emplace_back(UnaryOpNode(un_op_kind, &**--end()));
}