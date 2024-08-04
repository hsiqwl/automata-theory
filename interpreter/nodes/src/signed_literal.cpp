#include "signed_literal.h"
#include "node_visitor.h"

SignedLiteralNode::SignedLiteralNode(int value, const location_t &loc) : INode(NodeKind::SignedLiteral, loc), value_(value) {}

Value SignedLiteralNode::GetValue() const noexcept {
    return {SignedValue{value_}};
}

void SignedLiteralNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void SignedLiteralNode::PrintOut(std::ostream &stream) const {
    auto fmt_string = std::format("SignedLiteralNode with value: {}", std::any_cast<int>(value_.GetValue()));
    stream << fmt_string << '\n';
}