#ifndef REGEX_AST_H
#define REGEX_AST_H
#include "node.h"
#include <stack>
#include <functional>

class ast{
public:
    ast(const std::shared_ptr<node>& new_root);

    ast(node::node_type root_type, ast& left, ast& right);

    ast(node::node_type root_type, ast& sub_tree);

    [[nodiscard]] ast get_deep_copy() const;

    void traverse(const std::function<void (const node&)>&);

private:
    std::shared_ptr<node> root;

    [[nodiscard]] std::shared_ptr<node> find_most_left() const noexcept;

};


#endif //REGEX_AST_H
