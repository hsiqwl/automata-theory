#include "state.h"

state::state(const std::list<transition>& transitions_list){
    transitions.insert(transitions.end(), transitions_list.begin(), transitions_list.end());
}

state::state(const state& other) {
    transitions = other.transitions;
}

void state::add_transition(std::shared_ptr<state> &to, std::shared_ptr<matcher> &transition_matcher) {
    std::shared_ptr<state> from = std::make_shared<state>(*this);
    transitions.emplace_back(from, to, transition_matcher);
}

state& state::get_next_state(char c) {
    for(auto &t: transitions) {
        if (t.can_make_transition(c))
            return *t.get_to_state();
    }
}

std::list<transition>& state::get_transitions() noexcept {
    return transitions;
}

void state::remove_transition(std::shared_ptr<state> &to) {
    for(auto iter = transitions.begin(); iter != transitions.end(); ++iter){
        if(iter->get_to_state() == to){
            transitions.erase(iter);
            return;
        }
    }
}
