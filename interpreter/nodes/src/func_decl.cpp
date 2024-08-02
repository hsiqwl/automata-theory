#include "func_decl.h"
#include "node_visitor.h"

FuncDeclNode::FuncDeclNode(std::string_view func_name, std::unique_ptr<StatementListNode> &&body,
                           std::vector<std::unique_ptr<VarDeclNode>> &&params)
                   : INode(NodeKind::FuncDecl), func_name_(func_name), body_(std::move(body)), params_(std::move(params)) {}

const std::unique_ptr<StatementListNode> &FuncDeclNode::GetFuncBody() const noexcept {
    return body_;
}

const std::vector<std::unique_ptr<VarDeclNode>> &FuncDeclNode::GetFuncParams() const noexcept {
    return params_;
}

const std::string &FuncDeclNode::GetFuncName() const noexcept {
    return func_name_;
}

void FuncDeclNode::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void FuncDeclNode::PrintOut(std::ostream &stream) const {
    stream << "function declaration with '" << func_name_ << "' name\n";
}
