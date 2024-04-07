#ifndef REGEX_MATCHER_H
#define REGEX_MATCHER_H

class matcher{
public:
    matcher() = default;
    virtual bool matches(char c) = 0;
    virtual ~matcher() = default;
};

#endif //REGEX_MATCHER_H
