#ifndef REGEX_STATE_H
#define REGEX_STATE_H
#include <vector>
#include "transition.h"

class state{
private:
    size_t state_id;

    std::vector<transition> transitions;

public:
    static const size_t error_state_id = -1;

    state(size_t state_id);

    state(size_t state_id, const std::vector<transition>& transitions);

    [[nodiscard]] size_t get_state_id() const noexcept;

    void add_transition(const transition& transition);

    state& get_following_state(char c);
};

#endif //REGEX_STATE_H
