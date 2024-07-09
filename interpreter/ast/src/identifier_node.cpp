#include "identifier_node.h"

IdentifierNode::IdentifierNode(std::string id): Node(NodeKind::Identifier), id_(std::move(id)) {
    label_ = id_;
}

void IdentifierNode::PrintOut(std::ostream &stream) const {
    stream << "IdentifierNode: '" << label_ << "'\n";
}