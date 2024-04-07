#include "any_matcher.h"

any_matcher::any_matcher(): matcher() {}

bool any_matcher::matches(char c) {
    return true;
}