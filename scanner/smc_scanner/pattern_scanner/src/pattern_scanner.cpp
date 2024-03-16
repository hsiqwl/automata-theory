#include "scanner.h"


parser::parser(): basic_scanner(), _fsm(*this) {
    scanners.emplace_back(new join_scanner{});
    scanners.emplace_back(new create_scanner{});
    scanners.emplace_back(new id_scanner{});
}

std::string parser::move_string_to_next_token_start(std::string &string) {
    size_t next_token_start_pos = string.find_first_of(" \t(),");
    if(next_token_start_pos == std::string::npos)
        next_token_start_pos = string.size();
    if(next_token_start_pos == 0)
        next_token_start_pos = 1;
    std::string prev_token = string.substr(0, next_token_start_pos);
    string.erase(string.begin(), string.begin() + next_token_start_pos);
    return prev_token;
}

bool parser::validate_string(const std::string &string) {
    _fsm.setState(MainMap::start);
    std::string copy{string};
    while(!copy.empty()){
        _fsm.read_next_token(copy);
        if(_fsm.getState().getName() == MainMap::error.getName()) {
            return false;
        }
    }
    if(_fsm.getState().getName() == MainMap::finishing_first_command.getName()){
        collector.put_accumulated_info_into_table();
    }
    return is_valid;
}

std::pair<bool, std::optional<std::string>> parser::parse(const std::string &string) {
    bool string_valid = validate_string(string);
    std::optional<std::string> info_string = collector.get_resulting_info_string();
    return {string_valid, std::move(info_string)};
}
