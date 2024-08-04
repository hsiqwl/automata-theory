#include "statement_list.h"
#include "node_visitor.h"

StatementListNode::StatementListNode() : INode(NodeKind::StatementList, location_t()) {}

void StatementListNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void StatementListNode::AddStatement(std::unique_ptr<INode> &&statement) {
    if (statement != nullptr) {
        statements_.emplace(statements_.begin(), std::move(statement));
        location_.begin = statement->GetLocation().begin;
        location_.end = statements_.back()->GetLocation().end;
    }
}

std::size_t StatementListNode::NumOfStatements() const noexcept {
    return statements_.size();
}

const std::unique_ptr<INode> &StatementListNode::operator[](size_t index) const {
    return statements_[index];
}

void StatementListNode::PrintOut(std::ostream &stream) const {
    auto fmt_string = std::format("StatementListNode with {} statements", statements_.size());
    stream << fmt_string << '\n';
}