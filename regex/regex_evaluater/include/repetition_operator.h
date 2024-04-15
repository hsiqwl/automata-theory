#ifndef REGEX_REPETITION_OPERATOR_H
#define REGEX_REPETITION_OPERATOR_H
#include "operator_token.h"

struct repetition_operator: public operator_token{
    static const size_t MAX_POSSIBLE_REP = -1;

    size_t min_rep;

    size_t max_rep;

    repetition_operator(size_t _min_rep = 0, size_t _max_rep = MAX_POSSIBLE_REP);
};

#endif //REGEX_REPETITION_OPERATOR_H
