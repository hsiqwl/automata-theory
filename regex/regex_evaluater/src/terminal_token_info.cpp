#include "terminal_token_info.h"

terminal_token_info::terminal_token_info(char c) {
    type = terminal_type::single_character;
    range_min = c;
    range_max = c;
    is_negated = false;
}

terminal_token_info::terminal_token_info(std::string_view _singles, bool _is_negated) {
    type = terminal_type::character_class;
    is_negated = _is_negated;
    singles = _singles;
    range_min = 32;
    range_max = 32;
}

terminal_token_info::terminal_token_info(char _range_min, char _range_max, std::string_view _singles,
                                         bool _is_negated) {
    type = terminal_type::character_class;
    is_negated = _is_negated;
    singles = _singles;
    range_min = _range_min;
    range_max = _range_max;
}