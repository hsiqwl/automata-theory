#include "func_call.h"
#include "node_visitor.h"

FuncCallNode::FuncCallNode(std::string_view func_name, std::vector<std::unique_ptr<INode>> &&args)
    : INode(NodeKind::FuncCall), func_name_(func_name), args_(std::move(args)){}

const std::string &FuncCallNode::GetFuncName() const noexcept {
    return func_name_;
}

const std::vector<std::unique_ptr<INode>>& FuncCallNode::GetArgs() const noexcept {
    return args_;
}

void FuncCallNode::PrintOut(std::ostream &stream) const {
    stream << "calling '" << func_name_ << "' named func\n";
}

void FuncCallNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}