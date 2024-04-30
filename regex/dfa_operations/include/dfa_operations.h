#ifndef REGEX_DFA_OPERATIONS_H
#define REGEX_DFA_OPERATIONS_H
#include "dfa.h"

void make_complementation(dfa& automaton);

std::string regex_reconstruction(const dfa& automaton);


#endif //REGEX_DFA_OPERATIONS_H
