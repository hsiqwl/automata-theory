#include "unsigned_literal.h"
#include "node_visitor.h"

UnsignedLiteralNode::UnsignedLiteralNode(unsigned value, const location_t &loc)
        : INode(NodeKind::UnsignedLiteral, loc), value_(value) {}

void UnsignedLiteralNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

Value UnsignedLiteralNode::GetValue() const noexcept {
    return {UnsignedValue{value_}};
}

void UnsignedLiteralNode::PrintOut(std::ostream &stream) const {
    auto fmt_string = std::format("UnsignedLiteralNode with value:{}", std::any_cast<unsigned>(value_.GetValue()));
    stream << fmt_string << '\n';
}