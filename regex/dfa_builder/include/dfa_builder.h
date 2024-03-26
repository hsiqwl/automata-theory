#ifndef REGEX_DFA_BUILDER_H
#define REGEX_DFA_BUILDER_H

#include "token.h"
#include "regex_operator.h"
#include "regex_tokenizer.h"
#include <unordered_map>
#include <vector>
#include <stack>

class dfa_builder{
private:
    inline static std::unordered_map<char, regex_operator> operator_table{};

    static void fill_operator_table();

    static void handle_operator(std::stack<token>& operator_stack, std::vector<token>& postfix_token_sequence, token& token);

    static void handle_left_parenthesis(std::stack<token>& operator_stack, token& token);

    static void handle_right_parenthesis(std::stack<token>& operator_stack, std::vector<token>& postfix_token_sequence);

    static void handle_terminal(std::vector<token>& postfix_token_sequence, token& token);

public:
    static std::vector<token> infix_to_postfix(const std::vector<token>& infix_token_sequence); //in public for debugging
    // static dfa build(regex_tokenizer& regex);
};

#endif //REGEX_DFA_BUILDER_H
