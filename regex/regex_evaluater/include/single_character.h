#ifndef REGEX_TERMINAL_H
#define REGEX_TERMINAL_H
#include "token.h"

struct single_character: public token{
    char value;

    single_character(char c);
};

#endif //REGEX_TERMINAL_H
