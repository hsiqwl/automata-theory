#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H
#include "node_interface.h"
#include <any>

class Node {
public:
    template<class ConcreteNode>
    Node(ConcreteNode &&node): storage_(std::forward<ConcreteNode>(node)),
                               getter_([](std::any &storage) -> INode & {
                                   return std::any_cast<ConcreteNode &>(storage);
                               }) {}

    INode *operator->();

    INode &operator*();

private:
    std::any storage_;

    INode &(*getter_)(std::any &);
};

#endif //INTERPRETER_NODE_H
