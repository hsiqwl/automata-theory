#ifndef REGEX_TRANSITION_H
#define REGEX_TRANSITION_H
#include <memory>
#include "matcher.h"
#include "state.h"

class transition{
private:
    std::unique_ptr<state> from;

    std::shared_ptr<state> to;

    std::shared_ptr<matcher> transition_matcher;

public:
    transition(state& from, state& to, matcher& matcher);

    bool can_make_transition(char c);

    state& get_dest_state();
};

#endif //REGEX_TRANSITION_H
