#include "state.h"

state::state(size_t state_id, bool accepting) :state_id(state_id), accepting(accepting) {
    std::shared_ptr<state> from = std::make_shared<state>(std::move(*this));
    std::shared_ptr<state> to = std::make_shared<state>(-1);
    std::unique_ptr<matcher> transition_matcher{new any_matcher};
    transitions.emplace_back(from, to, std::move(transition_matcher));
}

state::state(size_t state_id, std::list<transition> &&_transitions, bool accepting = false)
    : state(state_id, accepting) {
    transitions.splice(transitions.end(),std::move(_transitions));
}

state::state(): state(error_state_id, false) {}

state::state(state &&other) noexcept{
    state_id = other.state_id;
    accepting = other.accepting;
    transitions = std::move(other.transitions);
}

state &state::operator = (state &&other) noexcept {
    if(this != &other){
        state_id = other.state_id;
        accepting = other.accepting;
        transitions.clear();
        transitions = std::move(other.transitions);
    }
    return *this;
}

size_t state::get_state_id() const noexcept {
    return state_id;
}

void state::make_accepting() noexcept {
    accepting = true;
}

void state::make_non_accepting() noexcept {
    accepting = false;
}

void state::add_transition(std::shared_ptr<state> &to, std::unique_ptr<matcher> &&transition_matcher) {
    if(not_error_state()) {
        std::shared_ptr<state> from = std::make_shared<state>(std::move(*this));
        transition new_transition(from ,to, std::move(transition_matcher));
        transitions.push_front(std::move(new_transition));
    }
}

bool state::not_error_state() const noexcept {
    return state_id != error_state_id;
}

state& state::get_next_state(char c) {
    for(auto &t: transitions) {
        if (t.can_make_transition(c))
            return t.get_to_state();
    }
}

bool state::is_accepting() const noexcept {
    return accepting;
}

std::list<transition>& state::get_transitions() noexcept {
    return transitions;
}

void state::remove_transition(std::shared_ptr<state> &to) {
    for(auto iter = transitions.begin(); iter != transitions.end(); ++iter){
        if(&iter->get_to_state() == to.get()){
            transitions.erase(iter);
            return;
        }
    }
}