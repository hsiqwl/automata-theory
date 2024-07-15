#ifndef INTERPRETER_IDENTIFIER_NODE_H
#define INTERPRETER_IDENTIFIER_NODE_H
#include "node_interface.h"

class IdentifierNode: public INode{
public:
    IdentifierNode(std::string_view id);

    void PrintOut(std::ostream& stream) const override;

    void Accept(NodeVisitor& visitor) override;

private:
    std::string id_;
};

#endif //INTERPRETER_IDENTIFIER_NODE_H
