#include "var_decl.h"
#include "node_visitor.h"

VarDeclNode::VarDeclNode(std::string_view name, const TypeHolder &type, const location_t &loc, bool is_const)
    : INode(NodeKind::VarDecl, loc), name_(name), type_(type), const_(is_const) {}

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

void VarDeclNode::PrintOut(std::ostream &stream) const {
    stream << "VarDeclNode for variable '" << name_ << "' with type: " << type_.GetStringRepresentation() << '\n';
}