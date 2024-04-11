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

    transition& operator = (transition&& other) noexcept;

    std::shared_ptr<state>& get_to_state();

    std::vector<size_t>& get_ending_groups() noexcept;

    std::vector<size_t>& get_starting_groups() noexcept;

    std::unique_ptr<matcher>& get_transition_matcher() noexcept;

    void replace_from_state(std::shared_ptr<state>& new_from);

    void replace_to_state(std::shared_ptr<state>& new_to);

    [[nodiscard]] bool ends_some_groups() const noexcept;

    [[nodiscard]] bool starts_some_groups() const noexcept;

    [[nodiscard]] bool can_make_transition(char c) const noexcept;

    [[nodiscard]] bool is_looped() const noexcept;
};

#endif //REGEX_TRANSITION_H
