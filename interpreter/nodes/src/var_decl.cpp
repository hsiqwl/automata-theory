#include "var_decl.h"
#include "node_visitor.h"

VarDeclNode::VarDeclNode(std::string_view name, const TypeHolder& type, bool is_const)
    : INode(NodeKind::VarDecl), name_(name), type_(type), const_(is_const) {
    label_ = name_;
}

void VarDeclNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

const std::string &VarDeclNode::GetName() const noexcept {
    return name_;
}

const TypeHolderWrapper & VarDeclNode::GetType() const noexcept {
    return type_;
}

bool VarDeclNode::IsConst() const noexcept {
    return const_;
}
