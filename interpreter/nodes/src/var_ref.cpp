#include "var_ref.h"
#include "node_visitor.h"

VarReferenceNode::VarReferenceNode(std::string_view name): INode(NodeKind::VarRef), var_name_(name) {
    label_ = var_name_;
}

const std::string &VarReferenceNode::GetVarName() const noexcept {
    return var_name_;
}

void VarReferenceNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}