#include "dfa_builder.h"

std::vector<std::unique_ptr<token>> dfa_builder::infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators) {
    reset_counter();
    std::stack<std::unique_ptr<token>> operator_stack;
    std::vector<std::unique_ptr<token>> postfix_token_sequence;
    for(auto& token_ptr = iterators.first; token_ptr != iterators.second; ++token_ptr) {
        switch ((*token_ptr)->type) {
            case token::token_type::terminal:
                handle_terminal(std::move(postfix_token_sequence), const_cast<std::unique_ptr<token> &&>(*token_ptr));
                break;
            case token::token_type::left_parenthesis:
                handle_left_parenthesis(std::move(operator_stack), const_cast<std::unique_ptr<token> &&>(*token_ptr));
                break;
            case token::token_type::op:
                handle_operator(std::move(operator_stack), std::move(postfix_token_sequence), const_cast<std::unique_ptr<token> &&>(*token_ptr));
                break;
            case token::token_type::right_parenthesis:
                handle_right_parenthesis(std::move(operator_stack), std::move(postfix_token_sequence));
                break;
        }
    }
    while (!operator_stack.empty()) {
        postfix_token_sequence.emplace_back(std::move(operator_stack.top()));
        operator_stack.pop();
    }
    return postfix_token_sequence;
}

void dfa_builder::handle_terminal(std::vector<std::unique_ptr<token>>&& postfix_token_sequence, std::unique_ptr<token>&& token_ptr) {
    postfix_token_sequence.emplace_back(std::move(token_ptr));
}

void dfa_builder::handle_left_parenthesis(std::stack<std::unique_ptr<token>> &&operator_stack, std::unique_ptr<token>&& token_ptr) {
    operator_stack.push(std::move(token_ptr));
}

void dfa_builder::handle_operator(std::stack<std::unique_ptr<token>> &&operator_stack, std::vector<std::unique_ptr<token>> &&postfix_token_sequence,
                                  std::unique_ptr<token>&& token_ptr) {
    while (!operator_stack.empty() && operator_stack.top()->type != token::token_type::left_parenthesis) {
        auto stack_token = dynamic_cast<operator_token&&>(*operator_stack.top());
        auto op_token = dynamic_cast<operator_token&&>(*token_ptr);
        unsigned short top_op_prec = stack_token.precedence;
        unsigned short curr_op_prec = op_token.precedence;
        if (top_op_prec >= curr_op_prec) {
            postfix_token_sequence.emplace_back(std::move(operator_stack.top()));
            operator_stack.pop();
        } else {
            break;
        }
    }
    operator_stack.push(std::move(token_ptr));
}

void dfa_builder::handle_right_parenthesis(std::stack<std::unique_ptr<token>> &&operator_stack, std::vector<std::unique_ptr<token>> &&postfix_token_sequence) {
    while (operator_stack.top()->type != token::token_type::left_parenthesis) {
        postfix_token_sequence.emplace_back(std::move(operator_stack.top()));
        operator_stack.pop();
    }
    operator_stack.pop();
}

void dfa_builder::reset_counter() noexcept {
    state_id_counter = 0;
}