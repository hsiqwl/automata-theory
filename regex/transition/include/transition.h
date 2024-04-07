#ifndef REGEX_TRANSITION_H
#define REGEX_TRANSITION_H
#include <memory>
#include "matcher.h"
#include <vector>

class state;

class transition{
private:
    std::vector<size_t> ends_groups;

    std::vector<size_t> starts_groups;

    std::shared_ptr<state> from;

    std::shared_ptr<state> to;

    std::unique_ptr<matcher> transition_matcher;

public:
    transition(std::shared_ptr<state>& from_state, std::shared_ptr<state>& to_state,
               std::unique_ptr<matcher>&& transition_matcher);

    transition(std::shared_ptr<state>& from_state, std::shared_ptr<state>& to_state,
               std::unique_ptr<matcher>&& transition_matcher, std::vector<size_t>& end_groups, std::vector<size_t>& start_groups);

    transition(transition&& other) noexcept;

    bool can_make_transition(char c);

    state& get_to_state();

    [[nodiscard]] bool ends_some_groups() const noexcept;

    [[nodiscard]] bool starts_some_groups() const noexcept;

    std::vector<size_t>& get_ending_groups() noexcept;

    std::vector<size_t>& get_starting_groups() noexcept;

    transition& operator = (transition&& other) noexcept;

};

#endif //REGEX_TRANSITION_H
