#ifndef REGEX_OPERATION_INFO_H
#define REGEX_OPERATION_INFO_H
#include <stddef.h>

struct operation_token_info{
    enum class operation_type{
        alternation,
        star,
        concatenation,
        optional,
        repetition
    };

    operation_type type;

    size_t precedence;

    size_t min_rep;

    size_t max_rep;

    operation_token_info(operation_type _type);

    operation_token_info(operation_type _type, size_t _min_rep, size_t _max_rep);
};

#endif //REGEX_OPERATION_INFO_H
