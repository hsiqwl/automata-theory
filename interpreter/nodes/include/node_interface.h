#ifndef INTERPRETER_NODE_INTERFACE_H
#define INTERPRETER_NODE_INTERFACE_H
#include "enums.h"
#include <memory>
#include <string>
#include "location.hh"

class NodeVisitor;

class INode {
public:
    using location_t = yy::location;

private:
    NodeKind kind_;

protected:
    location_t location_;

public:
    INode(NodeKind kind, const yy::location& location) : kind_(kind), location_(location){}

    NodeKind GetKind() const { return kind_; };

    const location_t & GetLocation() const noexcept { return location_;}

    virtual void Accept(NodeVisitor& visitor) const = 0;

    virtual ~INode() = default;
};

#endif //INTERPRETER_NODE_INTERFACE_H
