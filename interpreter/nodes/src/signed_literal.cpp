#include "signed_literal.h"
#include "node_visitor.h"

SignedLiteralNode::SignedLiteralNode(int value): INode(NodeKind::SignedLiteral), value_(value) {}

Value SignedLiteralNode::GetValue() const noexcept {
    return {SignedValue{value_}};
}

void SignedLiteralNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}