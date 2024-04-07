#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include "state.h"
#include "transition.h"

class dfa{
private:
    std::vector<std::shared_ptr<state>> states;

    std::shared_ptr<state> curr_state;

    std::shared_ptr<state> initial_state;

protected:
    void add_state(std::shared_ptr<state>&& state);

    void declare_states(std::initializer_list<std::shared_ptr<state>>&& states_list);

    void add_transition(std::shared_ptr<state>& from, std::shared_ptr<state>& to, std::unique_ptr<matcher>&& transition_matcher);

    void set_initial_state(std::shared_ptr<state>& initial);

    void set_accepting_states(std::initializer_list<std::shared_ptr<state>>& states_list);

public:
    dfa() = default;

};

#endif //REGEX_DFA_H
