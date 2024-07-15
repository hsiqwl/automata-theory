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

void NumericLiteralNode::PrintOut(std::ostream &stream) const {
    stream << "NumericLiteralNode :'" << label_ << "'\n";
}

void NumericLiteralNode::Accept(NodeVisitor &visitor) {
    visitor.Visit(*this);
}