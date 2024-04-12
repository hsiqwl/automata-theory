#include "state.h"

state::state(size_t state_id) :state_id(state_id) {
    std::shared_ptr<state> from = std::make_shared<state>(std::move(*this));
    std::shared_ptr<state> to = std::make_shared<state>();
    std::shared_ptr<matcher> transition_matcher{new any_matcher};
    transitions.emplace_back(from, to, transition_matcher);
}

state::state(size_t state_id, std::list<transition> &&transitions_list)
    : state(state_id) {
    transitions.splice(transitions.end(),transitions_list);
}

state::state() {
    state_id = error_state_id;
}

state::state(const state& other) {
    state_id = other.state_id;
}


size_t state::get_state_id() const noexcept {
    return state_id;
}

void state::add_transition(std::shared_ptr<state> &to, std::shared_ptr<matcher> &transition_matcher) {
    if(not_error_state()) {
        std::shared_ptr<state> from = std::make_shared<state>(*this);
        transition new_transition(from ,to, transition_matcher);
        transitions.push_front(new_transition);
    }
}

bool state::not_error_state() const noexcept {
    return state_id != error_state_id;
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