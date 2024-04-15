#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H

#include "regex_tokenizer.h"
#include <vector>
#include <stack>

class dfa_builder{
private:
    static void handle_operator(std::stack<std::unique_ptr<token>>&& operator_stack, std::vector<std::unique_ptr<token>>&& postfix_token_sequence, std::unique_ptr<token>&& token_ptr);

    static void handle_left_parenthesis(std::stack<std::unique_ptr<token>>&& operator_stack, std::unique_ptr<token>&& token_ptr);

    static void handle_right_parenthesis(std::stack<std::unique_ptr<token>>&& operator_stack, std::vector<std::unique_ptr<token>>&& postfix_token_sequence);

    static void handle_terminal(std::vector<std::unique_ptr<token>>&& postfix_token_sequence, std::unique_ptr<token>&& token_ptr);

    static std::vector<std::unique_ptr<token>> infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators);

public:
};

#endif //REGEX_DFA_BUILDER_H
