#include "state.h"

state::state(size_t state_id) :state_id(state_id) {}

state::state(size_t state_id, const std::vector<transition> &transitions):state_id(state_id), transitions(transitions) {}

size_t state::get_state_id() const noexcept {
    return state_id;
}

void state::add_transition(const transition& transition) {
    transitions.emplace_back(transition);
}

state& state::get_following_state(char c) {
    for(auto& _transition: transitions){
        if(_transition.can_make_transition(c)){
            return _transition.get_dest_state();
        }
    }
}