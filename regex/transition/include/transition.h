#ifndef REGEX_TRANSITION_H
#define REGEX_TRANSITION_H
#include <memory>
#include "matcher.h"
#include "state.h"

class transition{
private:
    std::vector<size_t> ends_groups;

    std::vector<size_t> starts_groups;

    std::shared_ptr<state> from;

    std::shared_ptr<state> to;

    std::shared_ptr<matcher> transition_matcher;

public:
    transition(const state& from, const state& to, const matcher& matcher,
               const std::vector<size_t>& starts_groups, const std::vector<size_t>& ends_groups);

    transition(const state& from, const state& to, const matcher& transition_matcher);

    transition(const transition& other) noexcept;

    bool can_make_transition(char c);

    state& get_dest_state();

    bool ends_some_groups() const noexcept;

    bool starts_some_groups() const noexcept;

    std::vector<size_t>& get_ending_groups() noexcept;

    std::vector<size_t>& get_starting_groups() noexcept;

    transition& operator = (const transition& other) noexcept;
};

#endif //REGEX_TRANSITION_H
