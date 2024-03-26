#include "regex_operator.h"

regex_operator::regex_operator(char operator_symbol, unsigned short precedence)
        : operator_symbol(operator_symbol), precedence(precedence){}
