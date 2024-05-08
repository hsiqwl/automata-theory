#include "group_tracker.h"

group_tracker::group_tracker(const std::unordered_set<size_t> &starting, const std::unordered_set<size_t> &ending,
                             bool is_repetitive): is_repetitive(is_repetitive) {
    size_t min_tracked_position = *std::min_element(starting.begin(), starting.end());
    size_t max_tracked_position = *std::max_element(ending.begin(), ending.end());
    for(auto i = min_tracked_position; i <= max_tracked_position; ++i){
        tracked_states.insert(i);
    }
    starting_states = starting;
    ending_states = ending;
}

std::string group_tracker::get_substring() const noexcept {
    return substring;
}

void group_tracker::transform_substring(const std::unordered_set<size_t> &curr_state, char input) {
    std::unordered_set<size_t> intersection;
    for(auto state: curr_state) {
        if (tracked_states.contains(state)) {
            intersection.insert(state);
        }
    }
    if(intersection.empty())
        return;
    if(contains_starting_states(intersection)) {
        if (!is_repetitive)
            substring.clear();
    }
    substring.push_back(input);
}

bool group_tracker::contains_ending_states(const std::unordered_set<size_t> &set) {
    return std::any_of(ending_states.begin(), ending_states.end(),
                       [&set](size_t state){return set.contains(state);});
}

bool group_tracker::contains_starting_states(const std::unordered_set<size_t> &set) {
    return std::any_of(starting_states.begin(), starting_states.end(),
                       [&set](size_t state) { return set.contains(state); });
}