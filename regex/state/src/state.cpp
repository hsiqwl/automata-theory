#include "state.h"

state::state(size_t state_id, bool accepting = false) :state_id(state_id), accepting(accepting) {}

state::state(size_t state_id, const std::vector<transition> &transitions, bool accepting = false):state_id(state_id), accepting(accepting), transitions(transitions) {}

state::state() {
    state_id = error_state_id;
    accepting = false;
}

size_t state::get_state_id() const noexcept {
    return state_id;
}

void state::add_transition(const transition& transition) {
    transitions.emplace_back(transition);
}

void state::add_transition(const state &from, const state &to, const matcher &transition_matcher) {
    transitions.emplace_back(from, to, transition_matcher);
}

state& state::get_following_state(char c) noexcept{
    for(auto& _transition: transitions){
        if(_transition.can_make_transition(c)){
            return _transition.get_dest_state();
        }
    }
}

void state::make_accepting() noexcept {
    accepting = true;
}

void state::make_non_accepting() noexcept {
    accepting = false;
}