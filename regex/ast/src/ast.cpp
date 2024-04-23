#include "ast.h"

ast::ast(const std::shared_ptr<node>& new_root) {
    root = new_root;
}

ast::ast(node::node_type root_type, ast &sub_tree) {
    if (root_type == node::node_type::star || root_type == node::node_type::optional) {
        root = std::make_shared<node>(root_type, sub_tree.root);
    }
    sub_tree.root->set_parent(root);
}

ast::ast(node::node_type root_type, ast &left, ast &right) {
    if(root_type == node::node_type::concat || root_type == node::node_type::alternation){
        root = std::make_shared<node>(root_type, left.root, right.root);
    }
    left.root->set_parent(root);
    right.root->set_parent(root);
}

void ast::visit_node(const std::function<void(const node &)> &visitor, const node &visiting_node) {
    if(visiting_node.get_node_type() == node::node_type::leaf){
        visitor(visiting_node);
    }
    if(visiting_node.get_node_type() == node::node_type::alternation || visiting_node.get_node_type() == node::node_type::concat){
        visit_node(visitor, visiting_node.get_left_child());
        visit_node(visitor, visiting_node.get_right_child());
        visitor(visiting_node);
    }
    if(visiting_node.get_node_type() == node::node_type::star || visiting_node.get_node_type() == node::node_type::optional){
        visit_node(visitor, visiting_node.get_left_child());
        visitor(visiting_node);
    }
}

void ast::traverse(const std::function<void(const node &)> &visitor) {
    visit_node(visitor, *root);
}