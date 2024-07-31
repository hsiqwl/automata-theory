#ifndef INTERPRETER_IF_NODE_H
#define INTERPRETER_IF_NODE_H
#include "node_interface.h"
#include "printable_interface.h"

class IfNode: public INode, public IPrintable {
    IfNode(std::unique_ptr<INode>&& predicate, std::unique_ptr<INode>&& body);

    const std::unique_ptr<INode>& GetPredicate() const noexcept;

    const std::unique_ptr<INode>& GetBody() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream& stream) const override;

private:
    std::unique_ptr<INode> predicate_;

    std::unique_ptr<INode> body_;
};

#endif //INTERPRETER_IF_NODE_H
