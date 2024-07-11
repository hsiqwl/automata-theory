#ifndef INTERPRETER_AST_H
#define INTERPRETER_AST_H
#include "node.h"
#include "binary_op.h"
#include "unary_op.h"
#include <memory>
#include <list>
#include "ast_iterator.h"

class Ast{
private:
    std::list<Node> tree_;

public:
    Ast(Node&& node);

    Ast(BinaryOpKind bin_op_kind, Ast&& lhs, Ast&& rhs);

    Ast(UnaryOpKind un_op_kind, Ast&& operand);

    typedef AstIterator<true> const_iterator;

    typedef AstIterator<false> iterator;

    iterator begin() noexcept;

    const_iterator begin() const noexcept;

    const_iterator end() const noexcept;

    iterator end() noexcept;

    const_iterator cbegin() const noexcept;

    const_iterator cend() const noexcept;
};

#endif //INTERPRETER_AST_H
