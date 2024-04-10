#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include "state.h"
#include "transition.h"
#include "dfa_builder.h"

class dfa{
private:
    std::vector<std::shared_ptr<state>> states;

    std::shared_ptr<state> initial_state;

protected:
    std::shared_ptr<state> curr_state;

    inline static size_t state_id_counter = 0;

    void add_state(std::shared_ptr<state>&& state);

    void declare_states(std::initializer_list<std::shared_ptr<state>>&& states_list);

    void add_transition(std::shared_ptr<state>& from, std::shared_ptr<state>& to, std::unique_ptr<matcher>&& transition_matcher);

    void set_initial_state(std::shared_ptr<state>&& initial);

    void set_accepting_states(std::initializer_list<std::shared_ptr<state>>&& states_list);

public:
    dfa() = default;

    static void reset_counter() noexcept;

    std::shared_ptr<state>& get_curr_state() noexcept;

    std::shared_ptr<state>& get_initial_state() noexcept;

    std::vector<std::shared_ptr<state>>& get_states() noexcept;

};

#endif //REGEX_DFA_H
