#ifndef REGEX_STATE_H
#define REGEX_STATE_H
#include <vector>
#include "transition.h"

class state{
private:
    size_t state_id;

    bool accepting;

    std::vector<transition> transitions;

public:
    static const size_t error_state_id = -1;

    state(size_t state_id, bool accepting);

    state(size_t state_id, const std::vector<transition>& transitions, bool accepting);

    state();

    [[nodiscard]] size_t get_state_id() const noexcept;

    void add_transition(const transition& transition);

    void add_transition(const state& from, const state& to, const matcher& transition_matcher);

    state& get_following_state(char c) noexcept;

    void make_accepting() noexcept;

    void make_non_accepting() noexcept;

};

#endif //REGEX_STATE_H
