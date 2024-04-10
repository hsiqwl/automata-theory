#ifndef REGEX_STATE_H
#define REGEX_STATE_H
#include <list>
#include <vector>
#include "transition.h"
#include "any_matcher.h"

class state{
private:
    size_t state_id;

    bool accepting;

    std::list<transition> transitions;

public:
    static const size_t error_state_id = -1;

    state(size_t state_id, bool accepting = false);

    state(size_t state_id, std::list<transition>&& transitions, bool accepting);

    state();

    state(state&& other) noexcept;

    state& operator = (state&& other) noexcept;

    [[nodiscard]] size_t get_state_id() const noexcept;

    void add_transition(std::shared_ptr<state>& to, std::unique_ptr<matcher>&& transition_matcher);

    void remove_transition(std::shared_ptr<state>& to);

    void make_accepting() noexcept;

    void make_non_accepting() noexcept;

    [[nodiscard]] bool not_error_state() const noexcept;

    [[nodiscard]] bool is_accepting() const noexcept;

    state& get_next_state(char c);

    std::list<transition>& get_transitions() noexcept;
};

#endif //REGEX_STATE_H
