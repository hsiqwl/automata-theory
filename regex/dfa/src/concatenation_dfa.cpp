#include "concatenation_dfa.h"

concatenation_dfa::concatenation_dfa(dfa &left, dfa &right): dfa() {
    std::shared_ptr<state>& right_side_initial = right.get_initial_state();
    add_state(std::move(right_side_initial));
    for(auto& left_side_state: left.get_states()){
        for(auto& _transition: left_side_state->get_transitions()){
            if(_transition.get_to_state().is_accepting()){

            }
        }
    }
}

void concatenation_dfa::detach_from_ending_state(dfa &left) {
    for(auto& left_side_state: left.get_states()){

    }
}