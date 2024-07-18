#ifndef INTERPRETER_BINARY_OP_H
#define INTERPRETER_BINARY_OP_H
#include "node_interface.h"
#include <string>

class BinaryOpNode: public INode{
public:
    BinaryOpNode(BinaryOpKind op_kind, std::unique_ptr<INode>&& lhs, std::unique_ptr<INode>&& rhs);

    void Accept(NodeVisitor& visitor) const override;

    [[nodiscard]] const std::unique_ptr<INode>& GetLeft() const noexcept;

    [[nodiscard]] const std::unique_ptr<INode>& GetRight() const noexcept;

    [[nodiscard]] BinaryOpKind GetOpKind() const noexcept;

private:
    BinaryOpKind op_kind_;

    std::unique_ptr<INode> lhs_;

    std::unique_ptr<INode> rhs_;

    void SetLabel();
};

#endif //INTERPRETER_BINARY_OP_H
