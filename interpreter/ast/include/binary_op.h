#ifndef INTERPRETER_BINARY_OP_H
#define INTERPRETER_BINARY_OP_H
#include "node.h"
#include <optional>
#include <memory>
#include <string>

class BinaryOpNode: public Node{
public:
    BinaryOpNode(BinaryOpKind op_kind, std::unique_ptr<Node>&& lhs, std::unique_ptr<Node>&& rhs);

    void PrintOut(std::ostream& stream) const override;

private:
    BinaryOpKind op_kind_;

    std::unique_ptr<Node> lhs_;

    std::unique_ptr<Node> rhs_;

    void SetLabel();
};

#endif //INTERPRETER_BINARY_OP_H
