#include "transition.h"

transition::transition(state &from, state &to, matcher &matcher): from(&from), to(&to),
    transition_matcher(&matcher) {}

state& transition::get_dest_state() {
    return *to;
}

bool transition::can_make_transition(char c) {
    return transition_matcher->matches(c);
}


