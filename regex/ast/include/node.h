#ifndef REGEX_NODE_H
#define REGEX_NODE_H
#include <set>
#include <memory>

class node {
public:
    enum class node_type{
        leaf,
        concat,
        alternation,
        star,
        optional
    };

private:
    bool nullable;

    std::shared_ptr<node> parent;

    std::shared_ptr<node> left_child;

    std::shared_ptr<node> right_child;

    node_type type;

    char label;

public:
    node(char label);

    node(node_type type, const std::shared_ptr<node>& left, const std::shared_ptr<node>& right);

    node(node_type type, const std::shared_ptr<node>& child);

    void set_parent(const std::shared_ptr<node>& parent_ptr);

    node_type get_node_type() const noexcept;

    const node& get_right_child() const noexcept;

    const node& get_left_child() const noexcept;

    char get_label() const noexcept;
};


#endif //REGEX_NODE_H
