#include "unsigned_literal.h"
#include "node_visitor.h"

UnsignedLiteralNode::UnsignedLiteralNode(unsigned int value): INode(NodeKind::UnsignedLiteral), value_(value) {}

void UnsignedLiteralNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

Value UnsignedLiteralNode::GetValue() const noexcept {
    return {UnsignedValue{value_}};
}
