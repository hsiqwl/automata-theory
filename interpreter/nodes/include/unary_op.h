#ifndef INTERPRETER_UNARY_OP_H
#define INTERPRETER_UNARY_OP_H
#include "node_interface.h"

class UnaryOpNode : public INode{
public:
    UnaryOpNode(UnaryOpKind op_kind, std::unique_ptr<INode>&& operand);

    void Accept(NodeVisitor& visitor) const override;

    [[nodiscard]] UnaryOpKind GetOpKind() const noexcept;

    const std::unique_ptr<INode>& GetOperand() const noexcept;

private:
    UnaryOpKind op_kind_;

    std::unique_ptr<INode> operand_;

    void SetLabel();
};

#endif //INTERPRETER_UNARY_OP_H
