#include "regex_tokenizer.h"
#include <iostream>

std::vector<token> regex_tokenizer::turn_into_token_sequence(std::string_view expression) {
    bool after_escape_character = false;
    std::vector<token> token_sequence;
    for (char c: expression) {
        if (c == '%' && !after_escape_character)
            after_escape_character = true;
        else if ((c == '|' || c == '.' || c == '*' || c == '?') && !after_escape_character)
            token_sequence.emplace_back(token::token_type::op, c);
        else if (c == '(' && !after_escape_character)
            token_sequence.emplace_back(token::token_type::left_parenthesis, c);
        else if (c == ')' && !after_escape_character)
            token_sequence.emplace_back(token::token_type::right_parenthesis, c);
        else {
            token_sequence.emplace_back(token::token_type::terminal, c);
            after_escape_character = false;
        }
    }
    add_concat_tokens(token_sequence);
    return token_sequence;
}

void regex_tokenizer::add_concat_tokens(std::vector<token> &token_sequence) {
    for (size_t i = 1; i < token_sequence.size(); ++i) {
        token prev_token = token_sequence[i - 1];
        token curr_token = token_sequence[i];
        bool first_predicate = curr_token.type == token::token_type::left_parenthesis ||
                               curr_token.type == token::token_type::terminal;
        bool second_predicate = prev_token.type == token::token_type::op &&
                                (prev_token.value == '*' || prev_token.value == '?');
        bool third_predicate = prev_token.type == token::token_type::right_parenthesis ||
                               prev_token.type == token::token_type::terminal;
        if (first_predicate && (second_predicate || third_predicate)) {
            token_sequence.emplace(token_sequence.begin() + i, token::token_type::op, '.');
        }
    }
}

void regex_tokenizer::assert_expression() {
    mismatched_parenthesis = 0;
    assert_first_token(token_sequence.front());
    assert_last_token(token_sequence.back());
    for (size_t i = 1; i < token_sequence.size() - 1; ++i) {
        if (token_sequence[i].type == token::token_type::op) {
            if (token_sequence[i].value == '.')
                assert_concatenation_operation(token_sequence[i - 1], token_sequence[i + 1]);
            else if (token_sequence[i].value == '*')
                assert_star_operation(token_sequence[i - 1]);
            else
                assert_alternation_operation(token_sequence[i - 1], token_sequence[i + 1]);
        }
        if (token_sequence[i].type == token::token_type::left_parenthesis) {
            mismatched_parenthesis++;
            assert_first_token(token_sequence[i + 1]);
        }
        if (token_sequence[i].type == token::token_type::right_parenthesis) {
            mismatched_parenthesis--;
            assert_last_token(token_sequence[i - 1]);
        }
    }
    if(mismatched_parenthesis != 0)
        throw std::exception();
}


void regex_tokenizer::assert_first_token(const token &token) {
    if (token.type == token::token_type::op || token.type == token::token_type::right_parenthesis)
        throw std::exception();
    if (token.type == token::token_type::left_parenthesis)
        mismatched_parenthesis++;
}

void regex_tokenizer::assert_last_token(const token &token) {
    if (token.type == token::token_type::op) {
        if (token.value == '.' || token.value == '|')
            throw std::exception();
    }
    if (token.type == token::token_type::left_parenthesis)
        throw std::exception();
    if (token.type == token::token_type::right_parenthesis)
        mismatched_parenthesis--;
}

void regex_tokenizer::assert_star_operation(const token &left_hand_token) {
    if(left_hand_token.type != token::token_type::terminal && left_hand_token.type != token::token_type::right_parenthesis)
        throw std::exception();
}

void regex_tokenizer::assert_alternation_operation(const token &left_hand_token, const token &right_hand_token) {
    assert_last_token(left_hand_token);
    assert_first_token(right_hand_token);
}

void regex_tokenizer::assert_concatenation_operation(const token &left_hand_token, const token &right_hand_token) {
    bool first_predicate = right_hand_token.type == token::token_type::left_parenthesis ||
                           right_hand_token.type == token::token_type::terminal;
    bool second_predicate = left_hand_token.type == token::token_type::op &&
                            (left_hand_token.value == '*' || left_hand_token.value == '?');
    bool third_predicate = left_hand_token.type == token::token_type::right_parenthesis ||
                           left_hand_token.type == token::token_type::terminal;
    if (!(first_predicate && (second_predicate || third_predicate))) {
        throw std::exception();
    }
}

regex_tokenizer::regex_tokenizer(std::string_view expression) {
    token_sequence = turn_into_token_sequence(expression);
    assert_expression();
}

std::vector<token> regex_tokenizer::get_token_sequence() const noexcept {
    return token_sequence;
}
