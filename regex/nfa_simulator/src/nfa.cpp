#include "nfa.h"

nfa::nfa(std::vector<std::unordered_set<size_t>> &&follow_positions,
         std::array<std::unordered_set<size_t>, 256> &&char_to_positions,
         std::unordered_set<size_t> &&initial_positions,
         std::unordered_set<size_t>&& last_positions){
    follow_pos = std::move(follow_positions);
    char_to_pos = std::move(char_to_positions);
    initial_pos = std::move(initial_positions);
    last_pos = std::move(last_positions);
    curr_pos = initial_pos;
}

void nfa::reset() noexcept {
    curr_pos = initial_pos;
}

bool nfa::is_in_accepting_state() const noexcept {
    return std::find_first_of(curr_pos.begin(), curr_pos.end(), last_pos.begin(), last_pos.end()) != curr_pos.end();
}

void nfa::consume_input(char c) {
    if (!curr_pos.empty()) {
        std::unordered_set<size_t> new_curr_pos;
        for (auto pos_of_char: char_to_pos[c]) {
            if (curr_pos.contains(pos_of_char)) {
                new_curr_pos.merge(std::unordered_set<size_t>{follow_pos[pos_of_char - 1].begin(),
                                                              follow_pos[pos_of_char - 1].end()});
            }
        }
        curr_pos = new_curr_pos;
    }
}

const std::unordered_set<size_t> &nfa::get_curr_positions() const noexcept {
    return curr_pos;
}