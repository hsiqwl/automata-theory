#include "character_dfa.h"


character_dfa::character_dfa(char c): dfa() {
    std::shared_ptr<state> initial {new state(state_id_counter++)};
    std::shared_ptr<state> ending {new state(state_id_counter++, true)};
    std::unique_ptr<matcher> transition_matcher{new single_character_matcher(c)};
    declare_states({initial, ending});
    add_transition(initial, ending, std::move(transition_matcher));
    set_initial_state(std::move(initial));
    curr_state = initial;
}

character_dfa::character_dfa(char range_min, char range_max, std::string_view singles, bool negated) {
    std::shared_ptr<state> initial {new state(state_id_counter++)};
    std::shared_ptr<state> ending {new state(state_id_counter++, true)};
    std::unique_ptr<matcher> transition_matcher {new character_class_matcher(range_min, range_max, singles, negated)};
    declare_states({initial, ending});
    add_transition(initial, ending, std::move(transition_matcher));
    set_initial_state(std::move(initial));
    curr_state = initial;
}