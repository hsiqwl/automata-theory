#ifndef REGEX_TERMINAL_OPERATOR_H
#define REGEX_TERMINAL_OPERATOR_H
#include "token.h"

struct terminal_token: public token{
    enum class terminal_type{
        single_character,
        character_class
    };

    terminal_type type;

    terminal_token(terminal_type type);
};

#endif //REGEX_TERMINAL_OPERATOR_H
