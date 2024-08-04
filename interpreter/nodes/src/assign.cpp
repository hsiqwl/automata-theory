#include "assign.h"
#include "node_visitor.h"

AssignNode::AssignNode(std::unique_ptr<INode> &&lhs, std::unique_ptr<INode> &&rhs, const yy::location& loc)
    : INode(NodeKind::Assign, loc), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

void AssignNode::PrintOut(std::ostream &stream) const {
    auto ftm_string = std::format("AssignNode: '<-'");
    stream << ftm_string << '\n';
}