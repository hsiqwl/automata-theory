#ifndef REGEX_TOKEN_H
#define REGEX_TOKEN_H

struct token{
    enum class token_type{
        op,
        left_parenthesis,
        right_parenthesis,
        terminal
    };

    token_type type;

    char value;

    token(token_type type, char value);
};

#endif //REGEX_TOKEN_H
