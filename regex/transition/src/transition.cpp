#include "transition.h"


transition::transition(const state &from, const state &to, const matcher& transition_matcher,const std::vector<size_t> &starts_groups, const std::vector<size_t> &ends_groups)
    : from(const_cast<state*>(&from)),
      to(const_cast<state*>(&to)),
      transition_matcher(const_cast<matcher*>(&transition_matcher)),
      starts_groups(starts_groups),
      ends_groups(ends_groups)
    {}

transition::transition(const state &from, const state &to, const matcher &transition_matcher):
    transition(from, to, transition_matcher, {}, {}){}

transition::transition(const transition &other) noexcept {
    ends_groups = other.ends_groups;
    starts_groups = other.starts_groups;
    from = other.from;
    to = other.from;
    transition_matcher = other.transition_matcher;
}

state& transition::get_dest_state() {
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

transition& transition::operator=(const transition &other) noexcept {
    if(&other != this){
        ends_groups = other.ends_groups;
        starts_groups = other.starts_groups;
        from = other.from;
        to = other.from;
        transition_matcher = other.transition_matcher;
    }
    return *this;
}