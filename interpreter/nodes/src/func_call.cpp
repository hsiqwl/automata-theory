#include "func_call.h"
#include "node_visitor.h"

FuncCall::FuncCall(std::string_view func_name, std::vector<std::unique_ptr<INode>> &&args)
    : INode(NodeKind::FuncCall), func_name_(func_name), args_(std::move(args)){}

const std::string &FuncCall::GetFuncName() const noexcept {
    return func_name_;
}

const std::vector<std::unique_ptr<INode>>& FuncCall::GetArgs() const noexcept {
    return args_;
}

void FuncCall::PrintOut(std::ostream &stream) const {
    stream << "function call with parameters: \n";
    for (const auto &arg: args_) {
        auto &printable = dynamic_cast<const IPrintable &>(*arg);
        printable.PrintOut(stream);
    }
}

void FuncCall::Accept(NodeVisitor &visitor) const {
    visitor.Visit(*this);
}