#ifndef INTERPRETER_ASSIGN_H
#define INTERPRETER_ASSIGN_H
#include "node_interface.h"

class AssignNode: public INode {
public:
    AssignNode(std::unique_ptr<INode> &&lhs, std::unique_ptr<INode> &&rhs);

    [[nodiscard]] const std::unique_ptr<INode> &GetLeft() const noexcept;

    [[nodiscard]] const std::unique_ptr<INode> &GetRight() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

private:
    std::unique_ptr<INode> lhs_;

    std::unique_ptr<INode> rhs_;
};

#endif //INTERPRETER_ASSIGN_H
