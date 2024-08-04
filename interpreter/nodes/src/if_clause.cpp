#include "if_node.h"
#include "node_visitor.h"

IfNode::IfNode(std::unique_ptr<INode> &&predicate, std::unique_ptr<INode> &&body, const location_t &loc)
    : INode(NodeKind::IfNode, loc), predicate_(std::move(predicate)), body_(std::move(body)) {}

const std::unique_ptr<INode> &IfNode::GetBody() const noexcept {
    return body_;
}

const std::unique_ptr<INode> &IfNode::GetPredicate() const noexcept {
    return predicate_;
}

void IfNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void IfNode::PrintOut(std::ostream &stream) const {
    stream << "IF NODE\n";
}