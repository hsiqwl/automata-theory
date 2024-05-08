#ifndef REGEX_GROUP_TRACKER_H
#define REGEX_GROUP_TRACKER_H
#include <unordered_set>
#include <string>
#include <algorithm>

class group_tracker{
private:
    std::unordered_set<size_t> tracked_states;

    std::unordered_set<size_t> starting_states;

    std::unordered_set<size_t> ending_states;

    bool is_repetitive;

    std::string substring;

    bool contains_starting_states(const std::unordered_set<size_t>& set);

    bool contains_ending_states(const std::unordered_set<size_t>& set);

public:
    group_tracker() = default;

    group_tracker(const std::unordered_set<size_t>& starting, const std::unordered_set<size_t>& ending, bool is_repetitive);

    void transform_substring(const std::unordered_set<size_t>& curr_state, char input);

    std::string get_substring() const noexcept;
};
#endif //REGEX_GROUP_TRACKER_H
