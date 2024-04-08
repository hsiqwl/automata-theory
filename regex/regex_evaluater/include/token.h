#ifndef REGEX_TOKEN_H
#define REGEX_TOKEN_H
#include "operation_token_info.h"
#include "terminal_token_info.h"

struct token{
    enum class token_type{
        op,
        left_parenthesis,
        right_parenthesis,
        terminal
    };

    union token_info{
        operation_token_info op_info;
        terminal_token_info terminal_info;
    };

    token_type type;

    token(token_type type, char value);
};

#endif //REGEX_TOKEN_H
