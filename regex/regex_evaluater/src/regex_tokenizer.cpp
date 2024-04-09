#include "regex_tokenizer.h"
#include <iostream>
std::unique_ptr<token> regex_tokenizer::get_repetition_token_ptr(const char* &iter) {
    switch (*iter) {
        case '+': {
            return std::unique_ptr<token>(new repetition_operator{1});
        }
        case '*':{
            return std::unique_ptr<token>(new repetition_operator{});
        }
        case '?':{
            return std::unique_ptr<token>(new repetition_operator{0,1});
        }
        case '{':{
            size_t min_rep, max_rep;
            parse_repetition_operator(++iter, min_rep, max_rep);
            return std::unique_ptr<token>(new repetition_operator{min_rep, max_rep});
        }
    }
}

void regex_tokenizer::parse_repetition_operator(const char *&iter, size_t& min_rep, size_t& max_rep) {
    min_rep = 0;
    max_rep = 0;
    bool first_value = true;
    for (; *iter != '}'; ++iter) {
        if (*iter == ' ')
            continue;
        if (*iter >= '0' && *iter <= '9' && first_value) {
            min_rep *= 10;
            min_rep += static_cast<int>(*iter) - static_cast<int>('0');
        } else if (*iter >= '0' && *iter <= '9' && !first_value) {
            max_rep *= 10;
            max_rep += static_cast<int>(*iter) - static_cast<int>('0');
        } else if (*iter == ',') {
            first_value = false;
        } else {
            throw std::invalid_argument("Invalid repetition operator");
        }
    }
    if (min_rep > max_rep) {
        throw std::invalid_argument("Invalid repetition operator");
    }
}

void regex_tokenizer::parse_character_class_terminal(const char *&iter, std::string &singles, char &range_min,
                                                     char &range_max) {
    bool single_range = true;
    singles.push_back(*iter);
    ++iter;
    for (; *iter != ']'; ++iter) {
        if (*iter == '-' && single_range) {
            if (*(iter + 1) == ']') {
                singles.push_back(*iter);
                single_range = true;
            } else {
                range_min = singles.back();
                singles.pop_back();
                range_max = *(iter + 1);
                single_range = false;
                ++iter;
                continue;
            }
        } else if (*iter == '-' && !single_range) {
            if ((*iter + 1) == ']') {
                singles.push_back(*iter);
            } else {
                throw std::invalid_argument("Invalid character class");
            }
        } else {
            singles.push_back(*iter);
        }
    }
}

void regex_tokenizer::turn_into_token_sequence(std::string_view expression) {
    bool after_escape_character = false;
    for(auto it = expression.begin(); it != expression.end(); ++it){
        char c = *it;
        if(c == '%' && !after_escape_character){
            after_escape_character = true;
        }else if((c == '*' || c == '+' || c == '?' || c == '{') && !after_escape_character){
            if(c == '{' && expression.find('}', std::distance(expression.begin(), it)) == std::string_view::npos){
                throw std::invalid_argument("Invalid repetition operator");
            }
            token_sequence.emplace_back(get_repetition_token_ptr(it));
        }else if(c == '.' && !after_escape_character){
            token_sequence.emplace_back(new operator_token(operator_token::operator_type::concatenation));
        }else if(c == '|' && !after_escape_character){
            token_sequence.emplace_back(new operator_token(operator_token::operator_type::alternation));
        }
        else if(c == '(' && !after_escape_character){
            token_sequence.emplace_back(new token{token::token_type::left_parenthesis});
        }
        else if(c == ')' && !after_escape_character){
            token_sequence.emplace_back(new token{token::token_type::right_parenthesis});
        }else if(c == '[' && !after_escape_character){
            if(expression.find(']', std::distance(expression.begin(), it))  == std::string_view::npos){
                throw std::invalid_argument("Invalid character class");
            }else{
                std::string singles;
                char range_min = '\0';
                char range_max = '\0';
                parse_character_class_terminal(++it, singles, range_min, range_max);
                token_sequence.emplace_back(new character_class(range_min, range_max, singles));
            }
        }
        else{
            token_sequence.emplace_back(new single_character(c));
            after_escape_character = false;
        }
    }
    add_concat_tokens();
}

void regex_tokenizer::add_concat_tokens() {
    for (auto iter = token_sequence.begin() + 1; iter != token_sequence.end(); ++iter) {
        token& prev_token = **(iter - 1);
        token& curr_token = **iter;
        bool first_predicate = curr_token.type == token::token_type::left_parenthesis ||
                               curr_token.type == token::token_type::terminal;
        if(!first_predicate)
            continue;
        bool second_predicate = prev_token.type == token::token_type::op;
        if(second_predicate) {
            auto &op_token = dynamic_cast<operator_token&>(prev_token);
            second_predicate = op_token.type == operator_token::operator_type::repetition;
        }
        bool third_predicate = prev_token.type == token::token_type::right_parenthesis ||
                               prev_token.type == token::token_type::terminal;
        if (second_predicate || third_predicate) {
            token_sequence.emplace(iter, new operator_token(operator_token::operator_type::concatenation));
        }
    }
}

void regex_tokenizer::assert_expression() {
    mismatched_parenthesis = 0;
    assert_first_token(*token_sequence.front());
    assert_last_token(*token_sequence.back());
    for (auto iter = token_sequence.begin() + 1; iter != token_sequence.end() - 1; ++iter) {
        if ((*iter)->type == token::token_type::op) {
            auto &op_token = dynamic_cast<operator_token &>(**iter);
            if (op_token.type == operator_token::operator_type::concatenation)
                assert_concatenation_operation(**(iter - 1), **(iter + 1));
            else if (op_token.type == operator_token::operator_type::repetition)
                assert_star_operation(**(iter - 1));
            else
                assert_alternation_operation(**(iter - 1), **(iter + 1));
        }
        if ((*iter)->type == token::token_type::left_parenthesis) {
            mismatched_parenthesis++;
            assert_first_token(**(iter + 1));
        }
        if ((*iter)->type == token::token_type::right_parenthesis) {
            mismatched_parenthesis--;
            assert_last_token(**(iter - 1));
        }
    }
    if (mismatched_parenthesis != 0)
        throw std::invalid_argument("Mismatched parenthesis");
}


void regex_tokenizer::assert_first_token(const token &token) {
    if (token.type == token::token_type::op || token.type == token::token_type::right_parenthesis)
        throw std::exception();
    if (token.type == token::token_type::left_parenthesis)
        mismatched_parenthesis++;
}

void regex_tokenizer::assert_last_token(const token &token) {
    if (token.type == token::token_type::op) {
        auto &op_token = dynamic_cast<const operator_token&>(token);
        if(op_token.type == operator_token::operator_type::concatenation ||
            op_token.type == operator_token::operator_type::alternation){
            throw std::invalid_argument("Last symbol can't be alternation or concatenation operation");
        }
    }
    if (token.type == token::token_type::left_parenthesis)
        throw std::invalid_argument("Last symbol can't be left parenthesis");
    if (token.type == token::token_type::right_parenthesis)
        mismatched_parenthesis--;
}

void regex_tokenizer::assert_star_operation(const token &left_hand_token) {
    if(left_hand_token.type != token::token_type::terminal && left_hand_token.type != token::token_type::right_parenthesis)
        throw std::invalid_argument("Invalid repetition operator operand");
}

void regex_tokenizer::assert_alternation_operation(const token &left_hand_token, const token &right_hand_token) {
    assert_last_token(left_hand_token);
    assert_first_token(right_hand_token);
}

void regex_tokenizer::assert_concatenation_operation(const token &left_hand_token, const token &right_hand_token) {
    bool first_predicate = right_hand_token.type == token::token_type::left_parenthesis ||
                           right_hand_token.type == token::token_type::terminal;
    bool second_predicate = left_hand_token.type == token::token_type::op;
    if(second_predicate){
        auto &op_token = dynamic_cast<const operator_token&>(left_hand_token);
        second_predicate = op_token.type == operator_token::operator_type::repetition;
    }
    bool third_predicate = left_hand_token.type == token::token_type::right_parenthesis ||
                           left_hand_token.type == token::token_type::terminal;
    if (!(first_predicate && (second_predicate || third_predicate))) {
        throw std::invalid_argument("Invalid concatenation operation operand");
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

