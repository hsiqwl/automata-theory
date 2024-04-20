#ifndef REGEX_REPETITION_INFO_H
#define REGEX_REPETITION_INFO_H
#include <cstddef>
#include <algorithm>

class repetition_info{
private:
    static const size_t MAX_UPPER_BOUND = 20;

    size_t lower_bound;

    size_t upper_bound;

public:
    repetition_info(size_t lower, size_t upper);
};

#endif //REGEX_REPETITION_INFO_H
