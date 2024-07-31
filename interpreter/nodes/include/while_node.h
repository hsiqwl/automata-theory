#ifndef INTERPRETER_WHILE_NODE_H
#define INTERPRETER_WHILE_NODE_H
#include "node_interface.h"
#include "printable_interface.h"

class WhileNode: public INode, public IPrintable{
public:
    WhileNode(std::unique_ptr<INode>&& predicate, std::unique_ptr<INode>&& body);

    const std::unique_ptr<INode>& GetPredicate() const noexcept;

    const std::unique_ptr<INode>& GetBody() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream& stream) const override;

private:
    std::unique_ptr<INode> predicate_;

    std::unique_ptr<INode> body_;
};

#endif //INTERPRETER_WHILE_NODE_H
