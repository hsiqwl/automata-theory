#include "while_node.h"
#include "node_visitor.h"

WhileNode::WhileNode(std::unique_ptr<INode> &&predicate, std::unique_ptr<INode> &&body, const yy::location &loc)
    : INode(NodeKind::WhileNode, loc), predicate_(std::move(predicate)), body_(std::move(body)) {}

const std::unique_ptr<INode> &WhileNode::GetBody() const noexcept {
    return body_;
}

const std::unique_ptr<INode> &WhileNode::GetPredicate() const noexcept {
    return predicate_;
}

void WhileNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void WhileNode::PrintOut(std::ostream &stream) const {
    stream << "WHILE NODE'\n'";
}
