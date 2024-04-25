#include "dfa.h"

void dfa::add_transition(char c, std::shared_ptr<state> &from, const std::shared_ptr<state> &to) {
    from->add_transition(c, to);
}

void dfa::make_state_accepting(std::shared_ptr<state>& state) {
    state->set_acceptance(true);
    accepting_states.push_back(state);
}

void dfa::set_initial_state(const std::shared_ptr<state>& initial) {
    initial_state = initial;
    curr_state = initial_state;
}

const std::vector<std::shared_ptr<state>> &dfa::get_states() const noexcept {
    return states;
}

const std::shared_ptr<state> &dfa::get_curr_state() const noexcept {
    return curr_state;
}

void dfa::add_state(const std::shared_ptr<state> &new_state) {
    states.emplace_back(new_state);
}

void dfa::reset() {
    curr_state = initial_state;
}
