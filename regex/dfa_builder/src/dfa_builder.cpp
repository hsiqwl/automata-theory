#include "dfa_builder.h"
#include <iostream>

void dfa_builder::calc_first_pos(node_ptr tree_node) {
    switch (tree_node->get_node_type()) {
        case node::node_type::leaf: {
            first_pos_table.emplace(tree_node, std::unordered_set<size_t>{leaf_counter});
            alphabet.insert(tree_node->get_label());
            char_to_pos_table[tree_node->get_label()].insert(leaf_counter);
            return;
        }
        case node::node_type::concat: {
            calc_first_pos_for_concat(tree_node);
            return;
        }
        case node::node_type::alternation: {
            calc_first_pos_for_alternation(tree_node);
            return;
        }
        default: {
            calc_first_pos_for_star(tree_node);
            return;
        }
    }
}

void dfa_builder::calc_last_pos(node_ptr tree_node) {
    switch (tree_node->get_node_type()) {
        case node::node_type::leaf: {
            last_pos_table.emplace(tree_node, std::unordered_set<size_t>{leaf_counter++});
            return;
        }
        case node::node_type::concat: {
            calc_last_pos_for_concat(tree_node);
            return;
        }
        case node::node_type::alternation: {
            calc_last_pos_for_alternation(tree_node);
            return;
        }
        default: {
            calc_last_pos_for_star(tree_node);
            return;
        }
    }
}

void dfa_builder::calc_first_pos_for_alternation(node_ptr tree_node) {
    auto& left_first_pos = first_pos_table[tree_node->get_left_child().get()];
    auto& right_first_pos = first_pos_table[tree_node->get_right_child().get()];
    auto union_set = position_set{left_first_pos.begin(), left_first_pos.end()};
    union_set.merge(position_set{right_first_pos.begin(), right_first_pos.end()});
    first_pos_table.emplace(tree_node, union_set);
}

void dfa_builder::calc_first_pos_for_star(node_ptr tree_node) {
    first_pos_table.emplace(tree_node, first_pos_table[tree_node->get_left_child().get()]);
}

void dfa_builder::calc_first_pos_for_concat(node_ptr tree_node) {
    first_pos_table.emplace(tree_node, first_pos_table[tree_node->get_left_child().get()]);
    if (tree_node->get_left_child()->is_nullable()) {
        auto& right_first_pos = first_pos_table[tree_node->get_right_child().get()];
        first_pos_table[tree_node].merge(position_set{right_first_pos.begin(), right_first_pos.end()});
    }
}

void dfa_builder::calc_last_pos_for_alternation(node_ptr tree_node) {
    auto left_last_pos = last_pos_table[tree_node->get_left_child().get()];
    auto right_last_pos = last_pos_table[tree_node->get_right_child().get()];
    left_last_pos.merge(right_last_pos);
    last_pos_table.emplace(tree_node, left_last_pos);
}

void dfa_builder::calc_last_pos_for_star(node_ptr tree_node) {
    last_pos_table.emplace(tree_node, last_pos_table[tree_node->get_left_child().get()]);
}

void dfa_builder::calc_last_pos_for_concat(node_ptr tree_node) {
    last_pos_table.emplace(tree_node, last_pos_table[tree_node->get_right_child().get()]);
    if (tree_node->get_right_child()->is_nullable()) {
        auto& left_last_pos = last_pos_table[tree_node->get_left_child().get()];
        last_pos_table[tree_node].merge(position_set{left_last_pos.begin(), left_last_pos.end()});
    }
}

void dfa_builder::calc_follow_pos(node_ptr tree_node) {
    if (tree_node->get_node_type() == node::node_type::concat) {
        for (auto pos: last_pos_table[tree_node->get_left_child().get()]) {
            auto& right_first_pos = first_pos_table[tree_node->get_right_child().get()];
            follow_positions[pos - 1].merge(position_set{right_first_pos.begin(), right_first_pos.end()});
        }
    } else if (tree_node->get_node_type() == node::node_type::star) {
        for (auto pos: last_pos_table[tree_node]) {
            auto& first_pos = first_pos_table[tree_node];
            follow_positions[pos - 1].merge(position_set{first_pos.begin(), first_pos.end()});
        }
    }
}


dfa_builder::dfa_builder(const ast &tree) {
    leaf_counter = 1;
    for (auto &tree_node: tree) {
        calc_first_pos(const_cast<node_ptr>(&tree_node));
        calc_last_pos(const_cast<node_ptr>(&tree_node));
    }
    follow_positions.resize(leaf_counter - 1);
    for(auto &tree_node: tree){
        calc_follow_pos(const_cast<node_ptr>(&tree_node));
    }
    for (auto &tree_node: tree) {
        std::cout << "{";
        for (auto i: first_pos_table[const_cast<node_ptr>(&tree_node)])
            std::cout << i << ',';
        std::cout << "} ";
        std::cout << tree_node.get_label() << "{";
        for (auto i: last_pos_table[const_cast<node_ptr>(&tree_node)])
            std::cout << i << ',';
        std::cout << "}\n";
    }
}


