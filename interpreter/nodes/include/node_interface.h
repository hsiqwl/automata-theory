#ifndef INTERPRETER_NODE_INTERFACE_H
#define INTERPRETER_NODE_INTERFACE_H
#include "enums.h"
#include <fstream>
#include <string>

class NodeVisitor;

class INode {
protected:
    std::string label_; //for debugging and printing

private:
    NodeKind kind_;

public:
    INode(NodeKind kind) : kind_(kind) {}

    NodeKind GetKind() const { return kind_; };

    virtual void PrintOut(std::ostream &stream) const = 0;

    virtual void Accept(NodeVisitor& visitor) = 0;

    virtual ~INode() = default;
};

#endif //INTERPRETER_NODE_INTERFACE_H
