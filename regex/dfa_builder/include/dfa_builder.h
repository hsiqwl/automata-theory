#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H

#include "regex_tokenizer.h"
#include <vector>
#include <stack>
#include <array>
#include <algorithm>

class dfa_builder{
private:
    size_t pos_counter = 1;

    std::array<std::vector<size_t>, 256> char_to_pos_table;

    std::string alphabet;

private:
    size_t get_index_by_position(size_t pos);

    void calculate_nullability_and_positions(std::vector<token>& token_sequence);

    static void set_nullability_for_alternation(token& operation_token, const token& left_child, const token& right_child);

    static void set_nullability_for_concatenation(token& operation_token, const token& left_child, const token& right_child);

    static void set_nullability_for_repetition(token& operation_token, const token& child);

    void set_positions_for_terminal(token& terminal);

    void set_positions_for_single_character(token& single_character);

    void set_positions_for_character_class(token& character_class);

    static void set_positions_for_alternation(token& operation_token, const token& left_child, const token& right_child);

    static void set_positions_for_concatenation(token& operation_token, const token& left_child, const token& right_child);

    void set_positions_for_repetition(token& operation_token, const token& child);

    void set_positions_for_closed_range(token& operation_token, const token& child);

    void set_positions_for_right_open_range(token& operation_token, const token& child);

    void set_positions_for_left_open_range(token& operation_token, const token& child);

    static void set_positions_for_open_range(token& operation_token, const token& child);

    std::vector<std::vector<size_t>> calculate_follow_pos(const std::vector<token>& token_sequence);

    void calculate_follow_pos_for_concatenation(const token& left_child, const token& right_child, std::vector<std::vector<size_t>>& follow_pos);

    void calculate_follow_pos_for_repetition(const token& node, std::vector<std::vector<size_t>>& follow_pos);

    void calculate_follow_pos_for_open_range(const token& node, std::vector<std::vector<size_t>>& follow_pos);

    void calculate_follow_pos_for_closed_range(const token& node, std::vector<std::vector<size_t>>& follow_pos);

    void calculate_follow_pos_for_right_open_range(const token& node, std::vector<std::vector<size_t>>& follow_pos);

    void calculate_follow_pos_for_left_open_range(const token& node, std::vector<std::vector<size_t>>& follow_pos);

    void add_character_to_alphabet(char c);

public:
    dfa_builder() = default;

    std::vector<std::vector<size_t>> get_pre_build_info(std::string_view expression);
};

#endif //REGEX_DFA_BUILDER_H
