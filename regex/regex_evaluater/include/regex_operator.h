#ifndef REGEX_REGEX_OPERATOR_H
#define REGEX_REGEX_OPERATOR_H

struct regex_operator{
    char operator_symbol;

    unsigned short precedence;

    regex_operator(char operator_symbol, unsigned short precedence);
};

#endif //REGEX_REGEX_OPERATOR_H
