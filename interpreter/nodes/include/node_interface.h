#ifndef INTERPRETER_NODE_INTERFACE_H
#define INTERPRETER_NODE_INTERFACE_H
#include "enums.h"
#include <memory>
#include <string>

class NodeVisitor;

class INode {
private:
    NodeKind kind_;

public:
    INode(NodeKind kind) : kind_(kind) {}

    NodeKind GetKind() const { return kind_; };

    virtual void Accept(NodeVisitor& visitor) const = 0;

    virtual ~INode() = default;
};

#endif //INTERPRETER_NODE_INTERFACE_H
