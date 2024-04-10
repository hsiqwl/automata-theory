#include "dfa.h"

void dfa::add_state(std::shared_ptr<state> &&state) {
    states.push_back(std::move(state));
}

void dfa::declare_states(std::initializer_list<std::shared_ptr<state>> &&states_list) {
    states.assign(states_list.begin(), states_list.end());
}

void dfa::add_transition(std::shared_ptr<state> &from, std::shared_ptr<state> &to,
                         std::unique_ptr<matcher> &&transition_matcher) {
    from->add_transition(to, std::move(transition_matcher));
}

void dfa::set_initial_state(std::shared_ptr<state> &&initial) {
    initial_state = initial;

}

void dfa::set_accepting_states(std::initializer_list<std::shared_ptr<state>> &&states_list) {
    for(auto& it : states_list)
        it->make_accepting();
}

std::shared_ptr<state>& dfa::get_curr_state() noexcept {
    return curr_state;
}

void dfa::reset_counter() noexcept {
    state_id_counter = 0;
}

std::vector<std::shared_ptr<state>> &dfa::get_states() noexcept {
    return states;
}

std::shared_ptr<state>& dfa::get_initial_state() noexcept {
    return initial_state;
}

dfa::dfa(char c) {
    std::shared_ptr<state> initial {new state(state_id_counter++)};
    std::shared_ptr<state> ending {new state(state_id_counter++, true)};
    std::unique_ptr<matcher> transition_matcher{new single_character_matcher(c)};
    declare_states({initial, ending});
    add_transition(initial, ending, std::move(transition_matcher));
    set_initial_state(std::move(initial));
    curr_state = initial;
}

dfa::dfa(char range_min, char range_max, std::string_view singles, bool negated) {
    std::shared_ptr<state> initial {new state(state_id_counter++)};
    std::shared_ptr<state> ending {new state(state_id_counter++, true)};
    std::unique_ptr<matcher> transition_matcher {new character_class_matcher(range_min, range_max, singles, negated)};
    declare_states({initial, ending});
    add_transition(initial, ending, std::move(transition_matcher));
    set_initial_state(std::move(initial));
    curr_state = initial;
}

void dfa::alternate(dfa &other) {
    auto after_other_initial = std::move(other.initial_state->get_transitions());
    std::for_each(after_other_initial.begin(), after_other_initial.end(),
                  [this](transition &_transition) { _transition.replace_from_state(initial_state); });
    if (initial_state->is_accepting() || other.initial_state->is_accepting()) {
        initial_state->make_accepting();
    }
    for (auto &_state: other.states) {
        if (_state != other.initial_state)
            add_state(std::move(_state));
    }
}

