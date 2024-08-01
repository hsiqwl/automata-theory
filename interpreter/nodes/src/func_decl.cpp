#include "func_decl.h"
#include "node_visitor.h"

FuncDecl::FuncDecl(std::string_view func_name, std::unique_ptr<StatementListNode> &&body,
                   std::vector<std::unique_ptr<VarDeclNode>> &&params)
                   : INode(NodeKind::FuncDecl), func_name_(func_name), body_(std::move(body)), params_(std::move(params)) {}

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
