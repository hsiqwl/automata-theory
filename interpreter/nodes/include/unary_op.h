#ifndef INTERPRETER_UNARY_OP_H
#define INTERPRETER_UNARY_OP_H
#include "node_interface.h"
#include <memory>

class UnaryOpNode : public INode{
public:
    UnaryOpNode(UnaryOpKind op_kind, INode* operand);

    void PrintOut(std::ostream& stream) const override;

private:
    UnaryOpKind op_kind_;

    INode* operand_;

    void SetLabel();
};

#endif //INTERPRETER_UNARY_OP_H
