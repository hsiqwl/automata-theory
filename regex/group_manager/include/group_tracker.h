#ifndef REGEX_GROUP_TRACKER_H
#define REGEX_GROUP_TRACKER_H
#include <unordered_set>
#include <string>
#include <algorithm>

class group_tracker{
private:
    std::unordered_set<size_t> tracked_states;

    std::unordered_set<size_t> starting_states;

    size_t start_min = 0;

    size_t end_max = 0;

    size_t position_of_end_symbol = 0;

    bool is_repetitive = false;

    std::string substring;

    bool contains_starting_states(const std::unordered_set<size_t>& set) const;

    bool within_subexpression_positions(const std::unordered_set<size_t>& curr_positions) const;

public:
    group_tracker() = default;

    group_tracker(const std::unordered_set<size_t>& starting, const std::unordered_set<size_t>& ending, bool is_repetitive, size_t pos_of_end);

    void transform_substring(const std::unordered_set<size_t>& curr_state, char input);

    std::string get_substring() const noexcept;
};
#endif //REGEX_GROUP_TRACKER_H
