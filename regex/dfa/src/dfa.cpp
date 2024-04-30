#include "dfa.h"

void dfa::add_transition(char c, std::shared_ptr<state> &from, const std::shared_ptr<state> &to) {
    from->add_transition(c, to);
}

void dfa::make_state_accepting(std::shared_ptr<state>& state) {
    state->set_acceptance(true);
    accepting_states.push_back(state);
}

void dfa::set_initial_state(const std::shared_ptr<state>& initial) {
    initial_state = initial;
    curr_state = initial_state;
}

const std::vector<std::shared_ptr<state>> &dfa::get_states() const noexcept {
    return states;
}

const std::shared_ptr<state> &dfa::get_curr_state() const noexcept {
    return curr_state;
}

void dfa::add_state(const std::shared_ptr<state> &new_state) {
    states.emplace_back(new_state);
}

void dfa::reset() {
    curr_state = initial_state;
}

void dfa::make_state_non_accepting(std::shared_ptr<state>& changed_state) {
    std::erase_if(states, [&changed_state](std::shared_ptr<state>& checked_state)->bool {return changed_state == checked_state;});
    changed_state->set_acceptance(false);
}

dfa::dfa(const dfa &other) {
    std::unordered_map<std::shared_ptr<state>, std::shared_ptr<state>> correspondence_table;
    std::for_each(other.states.begin(), other.states.end(),
                  [&correspondence_table](const std::shared_ptr<state> &copied_state) {
                      correspondence_table[copied_state] = std::make_shared<state>();
                      correspondence_table[copied_state]->set_acceptance(copied_state->is_accepting());
                  });
    states.resize(other.states.size());
    std::transform(other.states.begin(), other.states.end(), states.begin(),
                   [&correspondence_table](const std::shared_ptr<state> &other_state) {
                       for (unsigned short i = 0; i < 256; ++i) {
                           auto to_state = other_state->get_valid_transitions()[i].lock();
                           if (to_state != nullptr) {
                               correspondence_table[other_state]->add_transition(i, correspondence_table[to_state]);
                           }
                       }
                       return correspondence_table[other_state];
                   });
    for (auto &st: other.accepting_states) {
        accepting_states.push_back(correspondence_table[st]);
    }
    curr_state = correspondence_table[other.curr_state];
    initial_state = correspondence_table[other.initial_state];
}