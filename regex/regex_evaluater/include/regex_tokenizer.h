#ifndef REGEX_REGEX_EVALUATER_H
#define REGEX_REGEX_EVALUATER_H

#include <string_view>
#include <vector>
#include <memory>
#include <algorithm>
#include "token.h"

class regex_tokenizer{
private:
    std::vector<token> token_sequence;
    size_t mismatched_parenthesis = 0;

private:
    token get_repetition_token_ptr(std::string_view::iterator& iter);

    void parse_repetition_operator(std::string_view::iterator& iter, size_t& min_rep, size_t& max_rep);

    void parse_character_class_terminal(std::string_view::iterator& iter, std::string& singles, char& range_min, char& range_max);

    void turn_into_token_sequence(std::string_view expression);

    void add_concat_tokens();

    void assert_first_token(const token& token);

    void assert_last_token(const token& token);

    void assert_star_operation(const token& left_hand_token);

    void assert_alternation_operation(const token& left_hand_token, const token& right_hand_token);

    void assert_concatenation_operation(const token& left_hand_token, const token& right_hand_token);

    void assert_expression();
public:
    typedef std::vector<token>::const_iterator token_iterator;

    regex_tokenizer(std::string expression);

    std::pair<token_iterator, token_iterator> get_token_sequence() const noexcept;

};

#endif