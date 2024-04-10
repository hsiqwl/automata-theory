#include "dfa.h"
void dfa::add_state(std::shared_ptr<state> &&state) {
    states.push_back(std::move(state));
}

void dfa::declare_states(std::initializer_list<std::shared_ptr<state>> &&states_list) {
    states.assign(states_list.begin(), states_list.end());
}

void dfa::add_transition(std::shared_ptr<state> &from, std::shared_ptr<state> &to,
                         std::unique_ptr<matcher> &&transition_matcher) {
    from->add_transition(to, std::move(transition_matcher));
}

void dfa::set_initial_state(std::shared_ptr<state> &&initial) {
    initial_state = initial;

}

void dfa::set_accepting_states(std::initializer_list<std::shared_ptr<state>> &&states_list) {
    for(auto& it : states_list)
        it->make_accepting();
}

std::shared_ptr<state>& dfa::get_curr_state() noexcept {
    return curr_state;
}

void dfa::reset_counter() noexcept {
    state_id_counter = 0;
}

std::vector<std::shared_ptr<state>> &dfa::get_states() noexcept {
    return states;
}

std::shared_ptr<state>& dfa::get_initial_state() noexcept {
    return initial_state;
}