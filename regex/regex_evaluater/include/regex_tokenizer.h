#ifndef REGEX_REGEX_EVALUATER_H
#define REGEX_REGEX_EVALUATER_H

#include <string_view>
#include <vector>
#include "token.h"

class regex_tokenizer{
private:
    std::vector<token> token_sequence;
    inline static size_t mismatched_parenthesis;

private:

    static std::vector<token> turn_into_token_sequence(std::string_view expression);

    static void add_concat_tokens(std::vector<token>& token_sequence);

    static void assert_first_token(const token& token);

    static void assert_last_token(const token& token);

    static void assert_star_operation(const token& left_hand_token);

    static void assert_alternation_operation(const token& left_hand_token, const token& right_hand_token);

    static void assert_concatenation_operation(const token& left_hand_token, const token& right_hand_token);

    void assert_expression();
public:
    regex_tokenizer(std::string_view expression);

    [[nodiscard]] std::vector<token> get_token_sequence() const noexcept;
};

#endif