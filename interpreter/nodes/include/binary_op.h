#ifndef INTERPRETER_BINARY_OP_H
#define INTERPRETER_BINARY_OP_H
#include "node_interface.h"
#include <string>

class BinaryOpNode: public INode{
public:
    BinaryOpNode(BinaryOpKind op_kind, INode* lhs, INode* rhs);

    void PrintOut(std::ostream& stream) const override;

    void Accept(NodeVisitor& visitor) override;

private:
    BinaryOpKind op_kind_;

    INode* lhs_;

    INode* rhs_;

    void SetLabel();
};

#endif //INTERPRETER_BINARY_OP_H
