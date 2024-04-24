#include "dfa_builder.h"
#include <iostream>

void dfa_builder::calc_first_pos(node_ptr tree_node) {
    switch (tree_node->get_node_type()) {
        case node::node_type::leaf: {
            first_pos_table.emplace(tree_node, std::unordered_set<size_t>{leaf_counter});
            if(tree_node->get_label() != '#') {
                alphabet.insert(tree_node->get_label());
            }
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


dfa_builder::dfa_builder(const ast &tree): root(tree.get_root()) {
    leaf_counter = 1;
    pre_build(tree);
}

void dfa_builder::pre_build(const ast &tree) {
    for (auto &tree_node: tree) {
        calc_first_pos(const_cast<node_ptr>(&tree_node));
        calc_last_pos(const_cast<node_ptr>(&tree_node));
    }
    follow_positions.resize(leaf_counter - 1);
    for(auto &tree_node: tree){
        calc_follow_pos(const_cast<node_ptr>(&tree_node));
    }
    size_t i = 1;
    for(auto& set: follow_positions){
        std::cout << "position: " << i << "  follow positions:";
        for(auto pos: set){
            std::cout << pos << ' ';
        }
        std::cout<<'\n';
        ++i;
    }
}

dfa dfa_builder::build() {
    dfa automaton;

    std::unordered_map<std::set<size_t>, std::shared_ptr<state>> used_combinations;
    std::unordered_map<std::shared_ptr<state>, std::set<size_t>> state_to_combination;
    std::vector<std::shared_ptr<state>> unmarked_states;

    std::shared_ptr<state> initial_state = std::make_shared<state>();
    unmarked_states.emplace_back(initial_state);
    automaton.add_state(initial_state);
    automaton.set_initial_state(initial_state);
    std::set<size_t> initial_positions{first_pos_table[const_cast<node_ptr>(&root)].begin(), first_pos_table[const_cast<node_ptr>(&root)].end()};
    used_combinations.emplace(initial_positions, initial_state);
    state_to_combination.emplace(initial_state, initial_positions);

    while (!unmarked_states.empty()) {
        std::shared_ptr<state> curr_state = unmarked_states[0];
        unmarked_states.erase(unmarked_states.begin());
        for (char c: alphabet) {
            auto combination = get_positions_for_input_char(c, state_to_combination[curr_state]);
            if (!combination.empty()) {
                if (!is_contained_in(used_combinations, combination)) {
                    std::shared_ptr<state> new_state = std::make_shared<state>();
                    used_combinations.emplace(combination, new_state);
                    state_to_combination.emplace(new_state, combination);
                    unmarked_states.emplace_back(new_state);
                    automaton.add_state(new_state);
                    if(combination.contains(*char_to_pos_table['#'].begin())){
                        automaton.make_state_accepting(*new_state);
                    }
                }
                automaton.add_transition(c, curr_state, used_combinations[combination]);
            }
        }
    }
    return automaton;
}


std::set<size_t> dfa_builder::get_positions_for_input_char(char c, const std::set<size_t>& set) {
    std::set<size_t> result;
    for(auto pos: char_to_pos_table[c]) {
        if (set.contains(pos)) {
            result.insert(follow_positions[pos - 1].begin(), follow_positions[pos - 1].end());
        }
    }
    return result;
}

bool dfa_builder::is_contained_in(const std::unordered_map<std::set<size_t>, std::shared_ptr<state>>& used_combinations,
                                  const std::set<size_t> &set) {
    for(auto& elem: used_combinations){
        if(elem.first == set)
            return true;
    }
    return false;
}