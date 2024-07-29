#include "ast.h"

Ast::Ast(std::unique_ptr<INode> &&node) : root_(std::move(node)) {}

const std::unique_ptr<INode>& Ast::GetRoot() const noexcept {
    return root_;

}
