#ifndef REGEX_ANY_MATCHER_H
#define REGEX_ANY_MATCHER_H
#include "matcher.h"

class any_matcher: public matcher{
public:
    any_matcher();
    bool matches(char c) override;
    std::string matching_string() const noexcept override;
};


#endif //REGEX_ANY_MATCHER_H
