#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H

#include <array>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "ast.h"

class dfa_builder{
public:
    dfa_builder(const ast& tree);


private:
    size_t leaf_counter;

    typedef node* node_ptr;

    typedef std::unordered_set<size_t> position_set;

    std::unordered_map<node_ptr, position_set> first_pos_table;

    std::unordered_map<node_ptr, position_set> last_pos_table;

    std::vector<position_set> follow_positions;

    std::unordered_set<char> alphabet;

    std::array<position_set, 256> char_to_pos_table;

    void calc_first_pos(node_ptr tree_node);

    void calc_last_pos(node_ptr tree_node);

    void calc_follow_pos(node_ptr tree_node);

    void calc_first_pos_for_alternation(node_ptr tree_node);

    void calc_first_pos_for_concat(node_ptr tree_node);

    void calc_first_pos_for_star(node_ptr tree_node);

    void calc_last_pos_for_alternation(node_ptr tree_node);

    void calc_last_pos_for_concat(node_ptr tree_node);

    void calc_last_pos_for_star(node_ptr tree_node);
};

#endif //REGEX_DFA_BUILDER_H
