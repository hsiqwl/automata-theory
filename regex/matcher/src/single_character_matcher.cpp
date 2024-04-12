#include "single_character_matcher.h"

single_character_matcher::single_character_matcher(char c): matcher() {
    matching_char = c;
}

bool single_character_matcher::matches(char c) {
    return c == matching_char;
}

std::string single_character_matcher::matching_string() const noexcept {
    return std::format("{}", matching_char);
}