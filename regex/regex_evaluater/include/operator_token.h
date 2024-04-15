#ifndef REGEX_OPERATOR_TOKEN_H
#define REGEX_OPERATOR_TOKEN_H
#include "token.h"

struct operator_token: public token{
    enum class operator_type{
        repetition,
        alternation,
        concatenation
    };

    operator_type type; //const

    short precedence; //const

    operator_token(operator_type _type);
};


#endif //REGEX_OPERATOR_TOKEN_H
