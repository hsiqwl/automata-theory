#ifndef INTERPRETER_ASSIGN_H
#define INTERPRETER_ASSIGN_H
#include "node_interface.h"
#include "printable_interface.h"

class AssignNode: public INode, public IPrintable{
public:
    AssignNode(std::unique_ptr<INode> &&lhs, std::unique_ptr<INode> &&rhs, const location_t &loc);

    [[nodiscard]] const std::unique_ptr<INode> &GetLeft() const noexcept;

    [[nodiscard]] const std::unique_ptr<INode> &GetRight() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream& stream) const override;

private:
    std::unique_ptr<INode> lhs_;

    std::unique_ptr<INode> rhs_;
};

#endif //INTERPRETER_ASSIGN_H
