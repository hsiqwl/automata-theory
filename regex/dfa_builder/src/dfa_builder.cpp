#include "dfa_builder.h"

void dfa_builder::fill_operator_table() {
    operator_table.try_emplace('|', '|', 1);
    operator_table.try_emplace('.', '.', 2);
    operator_table.try_emplace('*', '*', 3);
    operator_table.try_emplace('?', '?', 3);
}

std::vector<token> dfa_builder::infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators) {
    fill_operator_table();
    std::stack<token> operator_stack;
    std::vector<token> postfix_token_sequence;
    auto handler = [&operator_stack, &postfix_token_sequence](const token& token){
        switch (token.type) {
            case token::token_type::terminal:
                handle_terminal(postfix_token_sequence, token);
                break;
            case token::token_type::left_parenthesis:
                handle_left_parenthesis(operator_stack, token);
                break;
            case token::token_type::op:
                handle_operator(operator_stack, postfix_token_sequence, token);
                break;
            case token::token_type::right_parenthesis:
                handle_right_parenthesis(operator_stack, postfix_token_sequence);
                break;
        }
    };
    std::for_each(iterators.first, iterators.second, handler);
    while (!operator_stack.empty()) {
        postfix_token_sequence.emplace_back(operator_stack.top());
        operator_stack.pop();
    }
    return postfix_token_sequence;
}

void dfa_builder::handle_terminal(std::vector<token> &postfix_token_sequence, const token &token) {
    postfix_token_sequence.emplace_back(token);
}

void dfa_builder::handle_left_parenthesis(std::stack<token> &operator_stack, const token &token) {
    operator_stack.push(token);
}

void dfa_builder::handle_operator(std::stack<token> &operator_stack, std::vector<token> &postfix_token_sequence,
                                  const token &token) {
    while (!operator_stack.empty() && operator_stack.top().type != token::token_type::left_parenthesis) {
        unsigned short top_op_prec = operator_table[operator_stack.top().value].precedence;
        unsigned short curr_op_prec = operator_table[token.value].precedence;
        if (top_op_prec >= curr_op_prec) {
            postfix_token_sequence.emplace_back(operator_stack.top());
            operator_stack.pop();
        } else {
            break;
        }
    }
    operator_stack.push(token);
}

void dfa_builder::handle_right_parenthesis(std::stack<token> &operator_stack, std::vector<token> &postfix_token_sequence) {
    while (operator_stack.top().type != token::token_type::left_parenthesis) {
        postfix_token_sequence.emplace_back(operator_stack.top());
        operator_stack.pop();
    }
    operator_stack.pop();
}