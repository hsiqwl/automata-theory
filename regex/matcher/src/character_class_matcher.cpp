#include "character_class_matcher.h"


character_class_matcher::character_class_matcher(std::string_view single_chars, bool is_negated = false):
        character_class_matcher('\0', '\0', single_chars, is_negated) {}

character_class_matcher::character_class_matcher(char min, char max, std::string_view single_chars,
                                                 bool is_negated): is_negated(is_negated), matcher() {
    range_min = min;
    range_max = max;
    singles = single_chars;
}

bool character_class_matcher::matches(char c) {
    return (c >= range_min && c <= range_max || singles.contains(c)) ^ is_negated;
}

std::string character_class_matcher::matching_string() const noexcept {
    return std::format("{} <= char <= {} or {}", range_min, range_max, singles);
}