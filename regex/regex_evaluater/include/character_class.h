#ifndef REGEX_CHARACTER_CLASS_H
#define REGEX_CHARACTER_CLASS_H
#include "terminal_token.h"
#include <string_view>

struct character_class: public terminal_token{
    std::string_view singles; // std::string

    char range_min;

    char range_max;

    character_class(char range_min, char range_max);

    character_class(char range_min, char range_max, std::string_view singles);
};

#endif //REGEX_CHARACTER_CLASS_H
