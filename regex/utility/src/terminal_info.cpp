#include "terminal_info.h"

terminal_info::terminal_info(char c) {
    range_min = c;
    range_max = c;
    singles = c;
}

terminal_info::terminal_info(char min, char max, const std::string& singles_set) {
    range_min = min;
    range_max = max;
    singles = singles_set;
}

char terminal_info::get_range_max() const noexcept {
    return range_max;
}

char terminal_info::get_range_min() const noexcept {
    return range_min;
}

std::string terminal_info::get_singles() const noexcept {
    return singles;
}