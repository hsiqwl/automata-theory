#include "group_tracker.h"

group_tracker::group_tracker(const std::unordered_set<size_t> &starting, const std::unordered_set<size_t> &ending,
                             bool is_repetitive, size_t pos_of_end): is_repetitive(is_repetitive) {
    start_min = *std::min_element(starting.begin(), starting.end());
    end_max = *std::max_element(ending.begin(), ending.end());
    for(auto i = start_min; i <= end_max; ++i){
        tracked_states.insert(i);
    }
    starting_states = starting;
    position_of_end_symbol = pos_of_end;
}

std::string group_tracker::get_substring() const noexcept {
    return substring;
}

void group_tracker::transform_substring(const std::unordered_set<size_t> &curr_state, char input) {
    if (within_subexpression_positions(curr_state)) {
        std::unordered_set<size_t> intersection;
        for (auto state: curr_state) {
            if (tracked_states.contains(state)) {
                intersection.insert(state);
            }
        }
        if (!intersection.empty()) {
            if (contains_starting_states(intersection)) {
                if (!is_repetitive)
                    substring.clear();
            }
            substring.push_back(input);
        }
    }
}
bool group_tracker::contains_starting_states(const std::unordered_set<size_t> &set) const{
    return std::any_of(starting_states.begin(), starting_states.end(),
                       [&set](size_t state) { return set.contains(state); });
}

bool group_tracker::within_subexpression_positions(const std::unordered_set<size_t> &curr_positions) const{
    std::unordered_set<size_t> curr_positions_without_end_pos = curr_positions;
    curr_positions_without_end_pos.erase(position_of_end_symbol);
    auto curr_max = std::max_element(curr_positions_without_end_pos.begin(), curr_positions_without_end_pos.end());
    return curr_max != curr_positions_without_end_pos.end() && *curr_max <= end_max;
}