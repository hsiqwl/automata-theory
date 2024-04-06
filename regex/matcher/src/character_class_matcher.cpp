#include "character_class_matcher.h"


character_class_matcher::character_class_matcher(std::string_view single_chars, bool is_negated = false):
        character_class_matcher(' ', ' ', single_chars, is_negated) {}

character_class_matcher::character_class_matcher(char min, char max, std::string_view single_chars,
                                                 bool is_negated): is_negated(is_negated) {
    range_min = min;
    range_max = max;
    singles = single_chars;
}

bool character_class_matcher::matches(char c) {
    return (c >= range_min && c <= range_max || singles.contains(c)) && !is_negated;
}