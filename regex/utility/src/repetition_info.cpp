#include "repetition_info.h"

repetition_info::repetition_info(size_t lower, size_t upper) {
    lower_bound = lower;
    upper_bound = std::min(upper, MAX_UPPER_BOUND);
}