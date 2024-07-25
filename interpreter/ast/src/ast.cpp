#include "ast.h"
#include "printer.h"
#include "interpreter.h"

Ast::Ast(std::unique_ptr<INode> &&node) : root_(std::move(node)) {}

void Ast::PrintOut(std::ostream &stream) const {
    AstPrinter printer;
    printer.buf_ = &stream;
    root_->Accept(printer);
}

/*long Ast::Evaluate() const {
    return Interpreter::GetValue(root_);
}*/
