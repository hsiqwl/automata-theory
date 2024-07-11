#include "identifier_node.h"

IdentifierNode::IdentifierNode(std::string_view id): INode(NodeKind::Identifier), id_(id) {
    label_ = id_;
}

void IdentifierNode::PrintOut(std::ostream &stream) const {
    stream << "IdentifierNode: '" << label_ << "'\n";
}