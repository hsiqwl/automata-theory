#include "../include/join_scanner.h"

bool join_scanner::validate_string(const std::string &string) {
    _fsm.setState(JoinMap::start);
    size_t i = 0;
    while(string[i] != ' ' && string[i]!='\t' && i < string.size()){
        _fsm.change_state(string[i]);
        if(_fsm.getState().getName() == JoinMap::error.getName())
            return false;
        ++i;
    }
    return is_valid;
}