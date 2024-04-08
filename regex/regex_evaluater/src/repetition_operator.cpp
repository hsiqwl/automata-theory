#include "repetition_operator.h"

repetition_operator::repetition_operator(size_t _min_rep, size_t _max_rep): operator_token(operator_token::operator_type::repetition) {
    min_rep = _min_rep;
    max_rep = _max_rep;
}

repetition_operator::repetition_operator(): repetition_operator(0) {}