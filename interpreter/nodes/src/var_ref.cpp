#include "var_ref.h"
#include "node_visitor.h"

VarReferenceNode::VarReferenceNode(std::string_view name): INode(NodeKind::VarRef), var_name_(name) {}

const std::string &VarReferenceNode::GetVarName() const noexcept {
    return var_name_;
}

void VarReferenceNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void VarReferenceNode::PrintOut(std::ostream &stream) const {
    stream << "VarReferenceNode for variable : '" << var_name_ << "'\n";
}