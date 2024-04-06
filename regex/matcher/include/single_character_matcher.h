#ifndef REGEX_SINGLE_CHARACTER_MATCHER_H
#define REGEX_SINGLE_CHARACTER_MATCHER_H
#include "matcher.h"

class single_character_matcher: public matcher{
private:
    char matching_char;

public:
    single_character_matcher(char c);

    bool matches(char c) override;
};

#endif //REGEX_SINGLE_CHARACTER_MATCHER_H
