#ifndef REGEX_CHARACTER_CLASS_MATCHER_H
#define REGEX_CHARACTER_CLASS_MATCHER_H
#include "matcher.h"
#include <string_view>

class character_class_matcher: public matcher{
private:
    bool is_negated;

    char range_min;

    char range_max;

    std::string_view singles;

public:
    character_class_matcher(std::string_view single_chars, bool is_negated);
    character_class_matcher(char min, char max, std::string_view single_chars, bool is_negated);

    bool matches(char c) override;
};

#endif //REGEX_CHARACTER_CLASS_MATCHER_H
