#ifndef REGEX_STATE_H
#define REGEX_STATE_H
#include <list>
#include <vector>
#include "transition.h"
#include "any_matcher.h"

class state{
private:
    std::list<transition> transitions;

public:
    state(const std::list<transition>& transitions);

    state() = default;

    state(const state& other);

    void add_transition(std::shared_ptr<state>& to, std::shared_ptr<matcher>& transition_matcher);

    void remove_transition(std::shared_ptr<state>& to);

    state& get_next_state(char c);

    std::list<transition>& get_transitions() noexcept;
};

#endif //REGEX_STATE_H
