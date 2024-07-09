#ifndef INTERPRETER_IDENTIFIER_NODE_H
#define INTERPRETER_IDENTIFIER_NODE_H
#include "node.h"

class IdentifierNode: public Node{
public:
    IdentifierNode(std::string id);

    void PrintOut(std::ostream& stream) const override;

private:
    std::string id_;
};

#endif //INTERPRETER_IDENTIFIER_NODE_H
