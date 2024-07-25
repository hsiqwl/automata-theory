#include "statement_list.h"
#include "node_visitor.h"

StatementListNode::StatementListNode() : INode(NodeKind::StatementList) {
    label_ = "StatementList";
}

void StatementListNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void StatementListNode::AddStatement(std::unique_ptr<INode> &&statement) {
    statements_.emplace_back(std::move(statement));
}

std::size_t StatementListNode::NumOfStatements() const noexcept {
    return statements_.size();
}

const std::unique_ptr<INode> &StatementListNode::operator[](int index) const {
    return statements_[index];
}