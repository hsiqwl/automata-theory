#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include "state.h"
#include "transition.h"
#include "single_character_matcher.h"
#include "character_class_matcher.h"
#include <algorithm>
#include <unordered_map>

class dfa{
private:
    std::vector<std::shared_ptr<state>> states;

    std::vector<std::shared_ptr<state>> accepting_states;

    std::shared_ptr<state> initial_state;

    std::shared_ptr<state> curr_state;

    void add_state(const std::shared_ptr<state>& state);

    void declare_states(const std::initializer_list<std::shared_ptr<state>>& states_list);

    void add_transition(std::shared_ptr<state>& from, std::shared_ptr<state>& to, std::shared_ptr<matcher>& transition_matcher);

    void set_initial_state(const std::shared_ptr<state>& initial);

    void set_accepting_states(const std::initializer_list<std::shared_ptr<state>>& states_list);

    dfa deep_copy() const;

public:
    dfa() = default;

    explicit dfa(char c);

    dfa(char range_min, char range_max, std::string_view singles, bool negated);

    dfa(const dfa& other);

    void concatenate(dfa& other);

    void alternate(dfa& other);

    void repeat(size_t min_rep, size_t max_rep);

    bool state_is_accepting(std::shared_ptr<state>& state);

    void make_state_accepting(std::shared_ptr<state>& state);

    void make_state_non_accepting(std::shared_ptr<state>& state);

    std::shared_ptr<state>& get_curr_state() noexcept;

    std::shared_ptr<state>& get_initial_state() noexcept;

    std::vector<std::shared_ptr<state>>& get_states() noexcept;

};

#endif //REGEX_DFA_H
