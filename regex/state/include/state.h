#ifndef REGEX_STATE_H
#define REGEX_STATE_H
#include <list>
#include <vector>
#include "transition.h"
#include "any_matcher.h"

class state{
private:
    size_t state_id;

    std::list<transition> transitions;

public:
    static const size_t error_state_id = -1;

    state(size_t state_id);

    state(size_t state_id, std::list<transition>&& transitions);

    state();

    state(const state& other);

    [[nodiscard]] size_t get_state_id() const noexcept;

    void add_transition(std::shared_ptr<state>& to, std::shared_ptr<matcher>& transition_matcher);

    void remove_transition(std::shared_ptr<state>& to);

    [[nodiscard]] bool not_error_state() const noexcept;

    state& get_next_state(char c);

    std::list<transition>& get_transitions() noexcept;
};

#endif //REGEX_STATE_H
