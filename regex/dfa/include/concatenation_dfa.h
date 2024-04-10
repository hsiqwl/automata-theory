#ifndef REGEX_CONCATENATION_DFA_H
#define REGEX_CONCATENATION_DFA_H
#include "dfa.h"

class concatenation_dfa: public dfa{
private:
    void detach_from_ending_state(dfa& left);

public:
    concatenation_dfa(dfa& left, dfa& right);
};

#endif //REGEX_CONCATENATION_DFA_H
