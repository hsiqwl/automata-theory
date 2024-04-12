#include "transition.h"
#include "state.h"

transition::transition(std::shared_ptr<state> &from_state, std::shared_ptr<state> &to_state,
                       std::shared_ptr<matcher> &transition_matcher_, std::vector<size_t> &end_groups,
                       std::vector<size_t> &start_groups) {
    from = from_state;
    to = to_state;
    transition_matcher = transition_matcher_;
    ends_groups = std::move(end_groups);
    starts_groups = std::move(start_groups);
}

transition::transition(std::shared_ptr<state> &from_state, std::shared_ptr<state> &to_state,
                       std::shared_ptr<matcher> &transition_matcher_) {
    from = from_state;
    to = to_state;
    transition_matcher = transition_matcher_;
}

transition::transition(const transition &other) {
    from = other.from;
    to = other.to;
    transition_matcher = other.transition_matcher;
    ends_groups = other.ends_groups;
    starts_groups = other.starts_groups;
}

std::shared_ptr<state>& transition::get_to_state() {
    return to;
}

bool transition::can_make_transition(char c) const noexcept {
    return transition_matcher->matches(c);
}

bool transition::ends_some_groups() const noexcept {
    return !ends_groups.empty();
}

bool transition::starts_some_groups() const noexcept {
    return !starts_groups.empty();
}

std::vector<size_t>& transition::get_ending_groups() noexcept {
    return ends_groups;
}

std::vector<size_t>& transition::get_starting_groups() noexcept {
    return starts_groups;
}

void transition::replace_from_state(std::shared_ptr<state> &new_from) {
    from = new_from;
}

void transition::replace_to_state(std::shared_ptr<state> &new_to) {
    to = new_to;
}

std::shared_ptr<matcher> &transition::get_transition_matcher() noexcept {
    return transition_matcher;
}

bool transition::is_looped() const noexcept {
    return from == to;
}