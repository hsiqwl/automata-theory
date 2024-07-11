#include "node.h"

INode *Node::operator->() {
    return &getter_(storage_);
}

INode &Node::operator*() {
    return getter_(storage_);
}
