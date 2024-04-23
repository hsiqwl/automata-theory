#ifndef REGEX_AST_H
#define REGEX_AST_H
#include "node.h"
#include <functional>

class ast{
public:
    ast(const std::shared_ptr<node>& new_root);

    ast(node::node_type root_type, ast& left, ast& right);

    ast(node::node_type root_type, ast& sub_tree);

    void traverse(const std::function<void (const node&)>&);

private:
    std::shared_ptr<node> root;

    void visit_node(const std::function<void (const node&)>&, const node& visiting_node);
};


#endif //REGEX_AST_H
