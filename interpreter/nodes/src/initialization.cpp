#include "initialization.h"
#include "node_visitor.h"

InitializationNode::InitializationNode(std::string_view var_to_init, std::unique_ptr<INode> &&init_expr)
    : INode(NodeKind::Initialization), var_to_init_(var_to_init), init_expr_(std::move(init_expr)) {}

const std::string &InitializationNode::GetVarName() const noexcept {
    return var_to_init_;
}

const std::unique_ptr<INode> &InitializationNode::GetInitExpr() const noexcept {
    return init_expr_;
}

void InitializationNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}