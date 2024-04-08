#include "operator_token.h"

operator_token::operator_token(operator_token::operator_type _type): token(token::token_type::op) {
    type = _type;
    switch (type) {
        case operator_type::repetition: {
            precedence = 3;
            break;
        }
        case operator_type::alternation: {
            precedence = 1;
            break;
        }
        case operator_type::concatenation: {
            precedence = 2;
            break;
        }
    }
}