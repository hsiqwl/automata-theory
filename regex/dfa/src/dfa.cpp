#include "dfa.h"

void dfa::declare_states(const std::initializer_list<state>& states_list) {
    for(auto& st: states_list)
        add_state(st);
}

void dfa::add_state(const state &new_state) {
    states.emplace_back(new_state);
}

void dfa::set_accepting_states(const std::initializer_list<state>& states_list) {
    for (auto &accept_st: states_list) {
        for (auto &st: states) {
            if (accept_st.get_state_id() == st.get_state_id()) {
                st.make_accepting();
                break;
            }
        }
    }
}

void dfa::add_transition(state &from, const state &to, const matcher &transition_matcher) {
    for(auto& st: states){
        if(st.get_state_id() == from.get_state_id()){
            st.add_transition(st, to, transition_matcher);
            return;
        }
    }
}