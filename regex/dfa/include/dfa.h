#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include "state.h"
#include "transition.h"

class dfa{
private:
    std::vector<state> states;

    state curr_state;

    state initial_state;

public:
    dfa() = default;

    void declare_states(const std::initializer_list<state>& states_list);

    void add_state(const state& new_state);

    void add_transition(state& from, const state& to, const matcher& transition_matcher);

    void set_initial_state(const state& state);

    void set_accepting_states(const std::initializer_list<state>& states_list);
};

#endif //REGEX_DFA_H
