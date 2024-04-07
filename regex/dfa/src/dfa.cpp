#include "dfa.h"

void dfa::add_state(state new_state) {
    states.emplace_back(std::move(new_state));
}

void dfa::set_accepting_states(std::initializer_list<state> &states_list) {

}