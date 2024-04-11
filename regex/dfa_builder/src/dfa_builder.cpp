#include "dfa_builder.h"

std::vector<std::unique_ptr<token>> dfa_builder::infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators) {
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

dfa dfa_builder::build(const regex_tokenizer &tokens) {
    dfa::reset_counter();
    std::vector<std::unique_ptr<token>> reverse_notation = infix_to_postfix(tokens.get_token_sequence());
    std::stack<dfa> dfa_stack;
    for(auto& token: reverse_notation) {
        token_to_dfa(std::move(token), dfa_stack);
    }
    dfa result = dfa_stack.top();
    dfa_stack.pop();
    return result;
}

void dfa_builder::token_to_dfa(std::unique_ptr<token> &&token, std::stack<dfa> &dfa_stack) {
    switch(token->type){
        case token::token_type::terminal:{
            terminal_to_dfa(std::move(token), dfa_stack);
            return;
        }
        case token::token_type::op:{
            operation_to_dfa(std::move(token),  dfa_stack);
            return;
        }
    }
}

void dfa_builder::terminal_to_dfa(std::unique_ptr<token> &&token, std::stack<dfa> &dfa_stack) {
    auto& terminal = dynamic_cast<terminal_token&>(*token);
    switch (terminal.type) {
        case terminal_token::terminal_type::single_character:{
            auto& single_char = dynamic_cast<single_character&>(terminal);
            dfa_stack.emplace(single_char.value);
            return;
        }
        case terminal_token::terminal_type::character_class:{
            auto & char_class = dynamic_cast<character_class&>(terminal);
            dfa_stack.emplace(char_class.range_min, char_class.range_max, char_class.singles);
            return;
        }
    }
}

void dfa_builder::operation_to_dfa(std::unique_ptr<token> &&token, std::stack<dfa> &dfa_stack) {
    auto &operation = dynamic_cast<operator_token &>(*token);
    switch (operation.type) {
        case operator_token::operator_type::repetition: {
            auto &repetition = dynamic_cast<repetition_operator &>(operation);
            dfa operand = dfa_stack.top();
            dfa_stack.pop();
            operand.repeat(repetition.min_rep, repetition.max_rep);
            dfa_stack.push(operand);
            return;
        }
        case operator_token::operator_type::alternation: {
            dfa first = dfa_stack.top();
            dfa_stack.pop();
            dfa second = dfa_stack.top();
            dfa_stack.pop();
            first.alternate(second);
            dfa_stack.push(first);
            return;
        }
        case operator_token::operator_type::concatenation: {
            dfa first = dfa_stack.top();
            dfa_stack.pop();
            dfa second = dfa_stack.top();
            dfa_stack.pop();
            first.concatenate(second);
            dfa_stack.push(first);
            return;
        }
    }
}