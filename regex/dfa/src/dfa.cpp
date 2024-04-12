#include "dfa.h"

void dfa::add_state(const std::shared_ptr<state> &state) {
    states.push_back(state);
}

void dfa::declare_states(const std::initializer_list<std::shared_ptr<state>>& states_list) {
    states.assign(states_list.begin(), states_list.end());
}

void dfa::add_transition(std::shared_ptr<state> &from, std::shared_ptr<state> &to,
                         std::shared_ptr<matcher>& transition_matcher) {
    from->add_transition(to, transition_matcher);
}

void dfa::set_initial_state(const std::shared_ptr<state> &initial) {
    initial_state = initial;
}

void dfa::set_accepting_states(const std::initializer_list<std::shared_ptr<state>> &states_list) {
    for(auto& it : states_list) {
        accepting_states.push_back(it);
    }
}

std::shared_ptr<state>& dfa::get_curr_state() noexcept {
    return curr_state;
}

std::vector<std::shared_ptr<state>> &dfa::get_states() noexcept {
    return states;
}

std::shared_ptr<state>& dfa::get_initial_state() noexcept {
    return initial_state;
}

bool dfa::state_is_accepting(std::shared_ptr<state> &checked_state) {
    return std::any_of(accepting_states.begin(), accepting_states.end(),
                       [&checked_state](std::shared_ptr<state>& state)->bool{
                           return state == checked_state;
    });
}

void dfa::make_state_accepting(std::shared_ptr<state> &state) {
    set_accepting_states({state});
}

void dfa::make_state_non_accepting(std::shared_ptr<state> &state) {
    for(auto iter = accepting_states.begin(); iter < accepting_states.end(); ++iter){
        if(*iter == state){
            accepting_states.erase(iter);
            return;
        }
    }
}

dfa::dfa(const dfa &other) {
    states = other.states;
    accepting_states = other.accepting_states;
    initial_state = other.initial_state;
    curr_state = other.curr_state;
}

dfa::dfa(char c) {
    std::shared_ptr<state> initial {new state()};
    std::shared_ptr<state> ending {new state()};
    std::shared_ptr<matcher> transition_matcher{new single_character_matcher(c)};
    declare_states({initial, ending});
    add_transition(initial, ending, transition_matcher);
    set_initial_state(initial);
    set_accepting_states({ending});
    curr_state = initial;
}

dfa::dfa(char range_min, char range_max, std::string_view singles, bool negated) {
    std::shared_ptr<state> initial {new state()};
    std::shared_ptr<state> ending {new state()};
    std::shared_ptr<matcher> transition_matcher {new character_class_matcher(range_min, range_max, singles, negated)};
    declare_states({initial, ending});
    add_transition(initial, ending, transition_matcher);
    set_initial_state(initial);
    set_accepting_states({ending});
    curr_state = initial;
}

void dfa::alternate(dfa &other) {
    auto& after_other_initial = other.initial_state->get_transitions();
    for (auto &transition: after_other_initial) {
        initial_state->add_transition(transition.get_to_state(), transition.get_transition_matcher());
    }
    if (state_is_accepting(initial_state) || other.state_is_accepting(other.initial_state))
        set_accepting_states({initial_state});
    for (auto &state: other.states) {
        if (state != other.initial_state) {
            add_state(state);
            if(other.state_is_accepting(state)){
                make_state_accepting(state);
            }
        }
    }
    other.initial_state = initial_state;
}

void dfa::concatenate(dfa &other) {
    auto& after_other_initial = other.initial_state->get_transitions();
    for (auto &state: accepting_states) {
        for (auto &transition: after_other_initial) {
            if (!transition.is_looped()) {
                state->add_transition(transition.get_to_state(), transition.get_transition_matcher());
            } else {
                state->add_transition(state, transition.get_transition_matcher());
            }
        }
        if (other.state_is_accepting(other.initial_state)) {
            make_state_accepting(state);
        }else{
            make_state_non_accepting(state);
        }
    }
     for (auto &state: other.states) {
        for (auto &transition: state->get_transitions()) {
            if (transition.get_to_state() == other.initial_state && state != other.initial_state) {
                for (auto &accepting_state: accepting_states)
                    state->add_transition(accepting_state, transition.get_transition_matcher());
            }
        }
        std::remove_if(state->get_transitions().begin(), state->get_transitions().end(),
                       [&other](transition &t) -> bool { return t.get_to_state() == other.initial_state; });
        if (state != other.initial_state) {
            add_state(state);
            if(other.state_is_accepting(state)){
                make_state_accepting(state);
            }
        }
    }
}

void dfa::repeat(size_t min_rep, size_t max_rep) {
    dfa init(*this);
    if (min_rep == -1) {
        for (auto &transition: initial_state->get_transitions()) {
            for (auto &state: accepting_states) {
                state->add_transition(transition.get_to_state(), transition.get_transition_matcher());
            }
        }
    } else {
        for (size_t i = 0; i + 1 < min_rep; ++i) {
            dfa copy(init);
            concatenate(copy);
        }
    }
    if (max_rep == -1 && min_rep != -1) {
        for (auto &transition: initial_state->get_transitions()) {
            for (auto &state: accepting_states) {
                state->add_transition(transition.get_to_state(), transition.get_transition_matcher());
            }
        }
    } else {
        for (size_t i = 0; i < max_rep - min_rep; ++i) {
            dfa copy(init);
            copy.set_accepting_states({copy.initial_state});
            concatenate(copy);
        }
    }
}