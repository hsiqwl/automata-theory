#include "initialization.h"
#include "node_visitor.h"

InitializationNode::InitializationNode(std::unique_ptr<VarDeclNode> &&var_to_init, std::unique_ptr<INode> &&init_expr,
                                       const location_t &loc)
    : INode(NodeKind::Initialization, loc), var_to_init_(std::move(var_to_init)), init_expr_(std::move(init_expr)) {}

const std::unique_ptr<VarDeclNode> &InitializationNode::GetVarToInit() const noexcept {
    return var_to_init_;
}

const std::unique_ptr<INode> &InitializationNode::GetInitExpr() const noexcept {
    return init_expr_;
}

void InitializationNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void InitializationNode::PrintOut(std::ostream &stream) const {
    stream << "InitializationNode for variable: '" << var_to_init_->GetName() << "'\n";
}