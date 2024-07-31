#include "func_decl.h"
#include "node_visitor.h"

FuncDecl::FuncDecl(std::string_view func_name): INode(NodeKind::FuncDecl), func_name_(func_name) {}

void FuncDecl::DefineBody(std::unique_ptr<StatementListNode> &&body) {
    body_ = std::move(body);
}

void FuncDecl::DefineParameter(std::unique_ptr<VarDeclNode> &&param) {
    params_.emplace_back(std::move(param));
}

const std::unique_ptr<StatementListNode> &FuncDecl::GetFuncBody() const noexcept {
    return body_;
}

const std::vector<std::unique_ptr<VarDeclNode>> &FuncDecl::GetFuncParams() const noexcept {
    return params_;
}

const std::string &FuncDecl::GetFuncName() const noexcept {
    return func_name_;
}

void FuncDecl::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}

void FuncDecl::PrintOut(std::ostream &stream) const {
    stream << "function declaration\n";
}
