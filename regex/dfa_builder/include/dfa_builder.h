#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H

#include "regex_tokenizer.h"
#include <vector>
#include <stack>

class dfa_builder{
private:
    static size_t pos_counter;

    static void handle_operator(std::stack<token>& operator_stack, std::vector<token>& postfix_token_sequence, const token& op_token);

    static void handle_left_parenthesis(std::stack<token>& operator_stack, const token& parenthesis_token);

    static void handle_right_parenthesis(std::stack<token>& operator_stack, std::vector<token>& postfix_token_sequence);

    static void handle_terminal(std::vector<token>& postfix_token_sequence,const token& terminal_token);

    static std::vector<token> infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators);

    static void calculate_nullability_and_positions(std::vector<token>& postfix_token_sequence);

    static void set_nullability_for_alternation(token& operation_token, const token& left_child, const token& right_child);

    static void set_nullability_for_concatenation(token& operation_token, const token& left_child, const token& right_child);

    static void set_nullability_for_repetition(token& operation_token, const token& child);

    static void set_positions_for_terminal(token& terminal);

    static void set_positions_for_alternation(token& operation_token, const token& left_child, const token& right_child);

    static void set_positions_for_concatenation(token& operation_token, const token& left_child, const token& right_child);

    static void set_positions_for_repetition(token& operation_token, const token& child);

    static void set_positions_for_closed_range(token& operation_token, const token& child);

    static void set_positions_for_right_open_range(token& operation_token, const token& child);

    static void set_positions_for_left_open_range(token& operation_token, const token& child);

    static void set_positions_for_open_range(token& operation_token, const token& child);

public:

};

#endif //REGEX_DFA_BUILDER_H
