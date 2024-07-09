#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H
#include "enums.h"
#include <fstream>
#include <string>


class Node{
protected:
    std::string label_; //for debugging and printing

private:
    NodeKind kind_;

public:
    Node(NodeKind kind): kind_(kind) {}

    NodeKind GetKind() const {return kind_;};

    virtual void PrintOut(std::ostream& stream) const = 0;

    virtual ~Node() = default;
};

#endif //INTERPRETER_NODE_H
