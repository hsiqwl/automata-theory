#include "transition.h"
#include "state.h"

transition::transition(std::shared_ptr<state> &from_state, std::shared_ptr<state> &to_state,
                       std::unique_ptr<matcher> &&transition_matcher_, std::vector<size_t> &end_groups,
                       std::vector<size_t> &start_groups) {
    from = from_state;
    to = to_state;
    transition_matcher = std::move(transition_matcher_);
    ends_groups = std::move(end_groups);
    starts_groups = std::move(start_groups);
}

transition::transition(std::shared_ptr<state> &from_state, std::shared_ptr<state> &to_state,
                       std::unique_ptr<matcher> &&transition_matcher_) {
    from = from_state;
    to = to_state;
    transition_matcher = std::move(transition_matcher_);
}

transition::transition(transition &&other) noexcept {
    from = other.from;
    to = other.to;
    transition_matcher = std::move(other.transition_matcher);
    ends_groups = std::move(other.ends_groups);
    starts_groups = std::move(other.ends_groups);
}

transition &transition::operator=(transition &&other) noexcept {
    if(this != &other) {
        from.reset(other.from.get());
        to.reset(other.to.get());
        transition_matcher = std::move(other.transition_matcher);
        ends_groups = std::move(other.ends_groups);
        starts_groups = std::move(other.starts_groups);
    }
    return *this;
}

state &transition::get_to_state() {
    return *to;
}

bool transition::can_make_transition(char c) {
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