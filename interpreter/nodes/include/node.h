#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H
#include "node_interface.h"
#include <any>
#include <concepts>

class Node {
public:
    template<typename ConcreteNode>
    requires (!std::is_same_v<ConcreteNode, Node> &&
            std::is_base_of_v<Node, ConcreteNode> &&
            std::is_convertible_v<const volatile ConcreteNode*, const volatile Node*>)
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
