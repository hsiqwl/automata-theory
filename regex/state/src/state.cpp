#include "state.h"

state::state() {
    accepting = false;
}

void state::set_acceptance(bool acceptance) {
    accepting = acceptance;
}

void state::add_transition(char c, const std::shared_ptr<state> &to_state) {
    transitions[static_cast<unsigned short>(c)] = to_state;
}

const std::shared_ptr<state> &state::get_following_state(char c) {
    return transitions[static_cast<unsigned short>(c)];
}

bool state::is_accepting() const noexcept {
    return accepting;
}