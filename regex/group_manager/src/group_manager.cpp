#include "group_manager.h"

void group_manager::manage_group(size_t group_number, group_tracker &&tracker) {
    groups[group_number] = std::move(tracker);
}

std::string group_manager::get_group_substring(size_t group_number) {
    return groups.find(group_number)->second.get_substring();
}

void group_manager::consume_input(char input) {
    for (auto& group: groups) {
        group.second.transform_substring(nfa_engine.get_curr_positions(), input);
    }
    nfa_engine.consume_input(input);
}

void group_manager::set_engine(nfa &&engine) {
    nfa_engine = std::move(engine);
}