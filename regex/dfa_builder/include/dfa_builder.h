#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H
#include <array>
#include <memory>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include "dfa.h"
#include "ast.h"
#include <boost/bimap.hpp>

namespace std {
    template<>
    struct hash<std::set<unsigned long>> {
        size_t operator()(const std::set<unsigned long> &set) const noexcept {
            size_t resulting_hash;
            for (auto elem: set) {
                resulting_hash += elem;
                resulting_hash *= elem;
            }
            return resulting_hash << 17;
        }
    };
}

class dfa_builder{
public:
    dfa_builder(const ast& tree);

    dfa build();

private:
    size_t leaf_counter;

    typedef node* node_ptr;

    typedef std::unordered_set<size_t> position_set;

    const node& root;

    std::unordered_map<node_ptr, position_set> first_pos_table;

    std::unordered_map<node_ptr, position_set> last_pos_table;

    std::vector<position_set> follow_positions;

    std::unordered_set<char> alphabet;

    std::array<position_set, 256> char_to_pos_table;

    void pre_build(const ast& tree);

    void calc_first_pos(node_ptr tree_node);

    void calc_last_pos(node_ptr tree_node);

    void calc_follow_pos(node_ptr tree_node);

    void calc_first_pos_for_alternation(node_ptr tree_node);

    void calc_first_pos_for_concat(node_ptr tree_node);

    void calc_first_pos_for_star(node_ptr tree_node);

    void calc_last_pos_for_alternation(node_ptr tree_node);

    void calc_last_pos_for_concat(node_ptr tree_node);

    void calc_last_pos_for_star(node_ptr tree_node);

    std::set<size_t> get_positions_for_input_char(char c, const std::set<size_t>& set);
};

#endif //REGEX_DFA_BUILDER_H
