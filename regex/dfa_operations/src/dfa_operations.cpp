#include "dfa_operations.h"

void make_complementation(dfa& automaton) {
    std::shared_ptr<state> false_error_state = std::make_shared<state>();
    false_error_state->set_acceptance(true);
    for (unsigned short i = 0; i < 256; ++i) {
        false_error_state->add_transition(i, false_error_state);
    }
    for (auto st: automaton.get_states()) {
        st->set_acceptance(!st->is_accepting());
        for (unsigned short i = 0; i < 256; ++i) {
            if (st->get_valid_transitions()[i].lock() == nullptr) {
                automaton.add_transition(i, st, false_error_state);
            }
        }
    }
    automaton.add_state(false_error_state);
}