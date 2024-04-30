#include "state.h"

state::state() {
    accepting = false;
}

void state::set_acceptance(bool acceptance) {
    accepting = acceptance;
}

void state::add_transition(char c, const std::shared_ptr<state> &to_state) {
    auto sym = static_cast<unsigned char>(c);
    auto index = static_cast<unsigned short>(sym);
    transitions[index] = to_state;
}

const std::weak_ptr<state> &state::get_following_state(char c) {
    auto sym = static_cast<unsigned char>(c);
    auto index = static_cast<unsigned short>(sym);
    return transitions[index];
}

bool state::is_accepting() const noexcept {
    return accepting;
}

const std::array<std::weak_ptr<state>, 256>& state::get_valid_transitions() const {
    return transitions;
}