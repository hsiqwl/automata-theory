#ifndef INTERPRETER_UNARY_OP_H
#define INTERPRETER_UNARY_OP_H
#include "node_interface.h"
#include "printable_interface.h"

class UnaryOpNode : public INode, public IPrintable{
public:
    UnaryOpNode(UnaryOpKind op_kind, std::unique_ptr<INode> &&operand, const location_t &loc);

    void Accept(NodeVisitor& visitor) const override;

    [[nodiscard]] UnaryOpKind GetOpKind() const noexcept;

    const std::unique_ptr<INode>& GetOperand() const noexcept;

    void PrintOut(std::ostream& stream) const override;

private:
    UnaryOpKind op_kind_;

    std::unique_ptr<INode> operand_;

    char GetLabel() const;
};

#endif //INTERPRETER_UNARY_OP_H
