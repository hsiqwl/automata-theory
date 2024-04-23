#include "ast.h"

ast::ast(const std::shared_ptr<node>& new_root) {
    root = new_root;
}

ast::ast(node::node_type root_type, ast &sub_tree) {
    if (root_type == node::node_type::star || root_type == node::node_type::optional) {
        root = std::make_shared<node>(root_type, sub_tree.root);
    }
    sub_tree.root->next = root;
}

ast::ast(node::node_type root_type, ast &left, ast &right) {
    if(root_type == node::node_type::concat || root_type == node::node_type::alternation){
        root = std::make_shared<node>(root_type, left.root, right.root);
    }
    left.root->next = right.find_most_left();
    right.root->next = root;
}

void ast::traverse(const std::function<void(const node &)> &visitor) {
    std::shared_ptr<node> visiting_node = find_most_left();
    while (visiting_node != nullptr) {
        visitor(*visiting_node);
        visiting_node = visiting_node->next;
    }
}

std::shared_ptr<node> ast::find_most_left() const noexcept {
    std::shared_ptr<node> most_left = root;
    while(most_left->left_child != nullptr){
        most_left = most_left->left_child;
    }
    return most_left;
}

ast ast::get_deep_copy() const{
    std::stack<std::shared_ptr<ast>> subtree;
    std::shared_ptr<node> curr_node = find_most_left();
    while(curr_node != nullptr) {
        auto type = curr_node->type;
        if (type == node::node_type::leaf) {
            subtree.emplace(std::make_shared<ast>(std::make_shared<node>(curr_node->label)));
        }
        if (type == node::node_type::concat) {
            std::shared_ptr<ast> right = subtree.top();
            subtree.pop();
            std::shared_ptr<ast> left = subtree.top();
            subtree.pop();
            subtree.emplace(std::make_shared<ast>(type, *left, *right));
        }
        if (type == node::node_type::alternation) {
            std::shared_ptr<ast> right = subtree.top();
            subtree.pop();
            std::shared_ptr<ast> left = subtree.top();
            subtree.pop();
            subtree.emplace(std::make_shared<ast>(type, *left, *right));
        }
        if (type == node::node_type::star || type == node::node_type::optional) {
            std::shared_ptr<ast> sub_tree = subtree.top();
            subtree.pop();
            subtree.emplace(std::make_shared<ast>(type, *sub_tree));
        }
        curr_node = curr_node->next;
    }
    return *subtree.top();
}