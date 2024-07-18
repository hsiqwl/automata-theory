#include "numeric_literal.h"
#include "node_visitor.h"

NumericLiteralNode::NumericLiteralNode(int value): INode(NodeKind::NumericLiteral), is_signed_(true) {
    value_.emplace<int>(value);
    label_ = std::to_string(value);
}

NumericLiteralNode::NumericLiteralNode(unsigned int value): INode(NodeKind::NumericLiteral), is_signed_(false) {
    value_.emplace<unsigned int>(value);
    label_ = std::to_string(value);
}


void NumericLiteralNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

long NumericLiteralNode::GetValue() const {
    if (value_.index() == 0) {
        return std::get<int>(value_);
    } else {
        return std::get<unsigned int>(value_);
    }
}