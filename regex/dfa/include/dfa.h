#ifndef REGEX_DFA_H
#define REGEX_DFA_H
#include "state.h"
#include <vector>
#include <algorithm>

class dfa{
public:
    void add_state(const std::shared_ptr<state>& new_state);

    void make_state_accepting(state& state);

    [[nodiscard]] const std::vector<std::shared_ptr<state>>& get_states() const noexcept;

    [[nodiscard]] const state& get_curr_state() const noexcept;

    void set_initial_state(const std::shared_ptr<state>& initial);

    void add_transition(char c, std::shared_ptr<state>& from, const std::shared_ptr<state>& to);

private:
    std::vector<std::shared_ptr<state>> states;

    std::vector<std::shared_ptr<state>> accepting_states;

    std::shared_ptr<state> curr_state;

    std::shared_ptr<state> initial_state;
};

#endif //REGEX_DFA_H
