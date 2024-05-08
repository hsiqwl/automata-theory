#include "dfa_minimizer.h"

void dfa_minimizer::minimize(dfa &automaton) {
    initialize_correspondence_table(automaton.states);
    std::vector<std::pair<size_t, std::array<size_t, 256>>> accepting_table;
    std::vector<std::pair<size_t, std::array<size_t, 256>>> non_accepting_table;
    initialize_transition_tables(accepting_table, non_accepting_table, automaton);
    minimize_table(accepting_table, automaton);
    minimize_table(non_accepting_table, automaton);
    std::vector<std::shared_ptr<state>> new_states;
    for(auto& transitions: accepting_table){
        new_states.emplace_back(std::move(automaton.states[transitions.first]));
    }
    automaton.accepting_states = new_states;
    for(auto& transitions: non_accepting_table){
        new_states.emplace_back(std::move(automaton.states[transitions.first]));
    }
    automaton.states = std::move(new_states);
}

void dfa_minimizer::initialize_correspondence_table(const std::vector<std::shared_ptr<state>> &states) {
    state_to_number.clear();
    for(auto iter = states.begin(); iter != states.end(); ++iter){
        state_to_number[*iter] = std::distance(states.begin(), iter);
    }
}

void dfa_minimizer::initialize_transition_tables(std::vector<std::pair<size_t, std::array<size_t, 256>>> &accepting_table,
                                                 std::vector<std::pair<size_t, std::array<size_t, 256>>> &non_accepting_table,
                                                 const dfa &automaton) {
    for (auto &state: automaton.states) {
        std::array<size_t, 256> transitions{};
        for (size_t i = 0; i < 256; ++i) {
            transitions[i] = state_to_number[state->get_following_state(i)];
        }
        if (state->is_accepting())
            accepting_table.emplace_back(state_to_number[state], transitions);
        else
            non_accepting_table.emplace_back(state_to_number[state], transitions);
    }
}

void dfa_minimizer::minimize_table(std::vector<std::pair<size_t, std::array<size_t, 256>>> &table, const dfa& automaton) {
    for (size_t i = 0; i < table.size(); ++i) {
        for (size_t j = 0; j < table.size(); ++j) {
            if (i != j && table[i].second == table[j].second &&
                table[j].first != state_to_number[automaton.initial_state]) {
                table.erase(table.begin() + j);
                --j;
            }
        }
    }
}