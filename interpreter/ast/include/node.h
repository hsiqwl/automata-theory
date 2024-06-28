#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H
#include "enums.h"
#include <fstream>
#include <string>

class node{
protected:
    std::string label; //for debugging and printing

private:
    node_type type;

public:
    node(node_type type): type(type) {}

    node_type get_type() const {return type;};

    virtual void print(std::ostream& stream) const = 0;

    virtual ~node() = default;
};

#endif //INTERPRETER_NODE_H
