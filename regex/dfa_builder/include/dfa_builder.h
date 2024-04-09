#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H

#include "token.h"
#include "regex_tokenizer.h"
#include "dfa.h"
#include <vector>
#include <stack>

class dfa_builder{
private:
    static size_t state_id_counter;

    static void handle_operator(std::stack<std::unique_ptr<token>>&& operator_stack, std::vector<std::unique_ptr<token>>&& postfix_token_sequence, std::unique_ptr<token>&& token_ptr);

    static void handle_left_parenthesis(std::stack<std::unique_ptr<token>>&& operator_stack, std::unique_ptr<token>&& token_ptr);

    static void handle_right_parenthesis(std::stack<std::unique_ptr<token>>&& operator_stack, std::vector<std::unique_ptr<token>>&& postfix_token_sequence);

    static void handle_terminal(std::vector<std::unique_ptr<token>>&& postfix_token_sequence, std::unique_ptr<token>&& token_ptr);

public:
    static std::vector<std::unique_ptr<token>> infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators);

    static void reset_counter() noexcept;


    // static dfa build(regex_tokenizer& regex);
};

#endif //REGEX_DFA_BUILDER_H
