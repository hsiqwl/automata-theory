#ifndef REGEX_TOKEN_H
#define REGEX_TOKEN_H
#include <optional>

struct token{
    enum class token_type{
        op,
        left_parenthesis,
        right_parenthesis,
        terminal
    };

    token_type type;

    token(token_type type);

    virtual ~token() = default;
};

#endif //REGEX_TOKEN_H
