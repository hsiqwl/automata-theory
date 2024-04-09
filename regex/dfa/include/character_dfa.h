#ifndef REGEX_SINGLE_CHARACTER_DFA_H
#define REGEX_SINGLE_CHARACTER_DFA_H
#include "dfa.h"

class character_dfa: public dfa{
public:
    character_dfa(char c);
    character_dfa(char range_min, char range_max, std::string_view singles, bool negated);
};


#endif //REGEX_SINGLE_CHARACTER_DFA_H
