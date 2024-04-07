#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include "state.h"
#include "transition.h"

class dfa{
private:
    std::vector<state> states;

    std::shared_ptr<state> curr_state;

    std::shared_ptr<state> initial_state;

protected:
    void add_state(state new_state);

    void declare_states(std::initializer_list<state>& states_list);

    void add_transition(state& from, const state& to, const matcher& transition_matcher);

    void set_initial_state(const state& state);

    void set_accepting_states(std::initializer_list<state>& states_list);

public:
    dfa() = default;

};

#endif //REGEX_DFA_H
