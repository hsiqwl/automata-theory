#include "assign.h"
#include "node_visitor.h"

AssignNode::AssignNode(std::unique_ptr<INode> &&lhs, std::unique_ptr<INode> &&rhs)
    : INode(NodeKind::Assign), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
    label_ = "<-";
}

const std::unique_ptr<INode> &AssignNode::GetLeft() const noexcept {
    return lhs_;
}

const std::unique_ptr<INode> &AssignNode::GetRight() const noexcept {
    return rhs_;
}

void AssignNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}