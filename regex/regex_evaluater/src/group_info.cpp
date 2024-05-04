#include "group_info.h"

void group_info::add_group(size_t group_number) {
    tracked_groups.emplace_back(group_number);
}

std::pair<group_info::const_iterator, group_info::const_iterator> group_info::get_tracked_groups() const noexcept {
    return {tracked_groups.cbegin(), tracked_groups.cend()};
}