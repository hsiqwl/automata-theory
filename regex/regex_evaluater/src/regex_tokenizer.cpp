#include "regex_tokenizer.h"

void regex_tokenizer::turn_into_token_sequence(std::string_view expression) {
    bool after_escape_character = false;
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
    add_concat_tokens();
}

void regex_tokenizer::add_concat_tokens() {
    for (auto iter = token_sequence.begin() + 1; iter != token_sequence.end(); ++iter) {
        token prev_token = *(iter - 1);
        token curr_token = *iter;
        bool first_predicate = curr_token.type == token::token_type::left_parenthesis ||
                               curr_token.type == token::token_type::terminal;
        bool second_predicate = prev_token.type == token::token_type::op &&
                                (prev_token.value == '*' || prev_token.value == '?');
        bool third_predicate = prev_token.type == token::token_type::right_parenthesis ||
                               prev_token.type == token::token_type::terminal;
        if (first_predicate && (second_predicate || third_predicate)) {
            token_sequence.emplace(iter, token::token_type::op, '.');
        }
    }
}

void regex_tokenizer::assert_expression() {
    mismatched_parenthesis = 0;
    assert_first_token(token_sequence.front());
    assert_last_token(token_sequence.back());
    for (auto iter = token_sequence.begin() + 1; iter != token_sequence.end() - 1; ++iter) {
        if (iter->type == token::token_type::op) {
            if (iter->value == '.')
                assert_concatenation_operation(*(iter - 1), *(iter + 1));
            else if (iter->value == '*')
                assert_star_operation(*(iter - 1));
            else
                assert_alternation_operation(*(iter - 1), *(iter + 1));
        }
        if (iter->type == token::token_type::left_parenthesis) {
            mismatched_parenthesis++;
            assert_first_token(*(iter + 1));
        }
        if (iter->type == token::token_type::right_parenthesis) {
            mismatched_parenthesis--;
            assert_last_token(*(iter - 1));
        }
    }
    if (mismatched_parenthesis != 0)
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
    mismatched_parenthesis = 0;
    turn_into_token_sequence(expression);
    assert_expression();
}

std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator> regex_tokenizer::get_token_sequence() const noexcept {
    return {token_sequence.begin(), token_sequence.end()};
}

