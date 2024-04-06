#include "single_character_matcher.h"

single_character_matcher::single_character_matcher(char c) {
    matching_char = c;
}

bool single_character_matcher::matches(char c) {
    return c == matching_char;
}