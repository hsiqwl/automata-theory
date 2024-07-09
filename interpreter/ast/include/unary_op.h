#ifndef INTERPRETER_UNARY_OP_H
#define INTERPRETER_UNARY_OP_H
#include "node.h"
#include <memory>

class UnaryOpNode : public Node{
public:
    UnaryOpNode(UnaryOpKind op_kind, std::unique_ptr<Node>&& operand);

    void PrintOut(std::ostream& stream) const override;

private:
    UnaryOpKind op_kind_;

    std::unique_ptr<Node> operand_;

    void SetLabel();
};

#endif //INTERPRETER_UNARY_OP_H
