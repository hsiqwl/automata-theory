#include "operation_token_info.h"

operation_token_info::operation_token_info(operation_token_info::operation_type _type) {
    min_rep = 1;
    max_rep = 1;
    type = _type;
    switch (type) {
        case operation_type::alternation: {
            precedence = 1;
            break;
        }
        case operation_type::star:{
            precedence = 3;
        }
        case operation_type::concatenation:{
            precedence = 2;
            break;
        }
        case operation_type::optional:{
            precedence = 3;
            break;
        }
        case operation_type::repetition:{
            precedence =  3;
            break;
        }
    }
}

operation_token_info::operation_token_info(operation_token_info::operation_type _type, size_t _min_rep,
                                           size_t _max_rep): operation_token_info(_type) {
    min_rep = _min_rep;
    max_rep = _max_rep;
}