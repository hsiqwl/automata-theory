#ifndef REGEX_TERMINAL_H
#define REGEX_TERMINAL_H
#include "terminal_token.h"

struct single_character: public terminal_token{
    char value;

    single_character(char c);
};

#endif //REGEX_TERMINAL_H
