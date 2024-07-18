#include "ast.h"
#include "printer.h"
#include "interpreter.h"

Ast::Ast(std::unique_ptr<INode> &&node) : root_(std::move(node)) {}

Ast::Ast(BinaryOpKind bin_op_kind, Ast &&lhs, Ast &&rhs)
    : root_(std::make_unique<BinaryOpNode>(bin_op_kind, std::move(lhs.root_), std::move(rhs.root_))) {}

Ast::Ast(UnaryOpKind un_op_kind, Ast &&operand)
    : root_(std::make_unique<UnaryOpNode>(un_op_kind, std::move(operand.root_))) {}

void Ast::PrintOut(std::ostream &stream) const {
    AstPrinter printer;
    printer.buf_ = &stream;
    root_->Accept(printer);
}

/*long Ast::Evaluate() const {
    return Interpreter::GetValue(root_);
}*/
