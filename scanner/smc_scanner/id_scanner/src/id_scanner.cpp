#include "../include/id_scanner.h"
#include <iostream>
bool id_scanner::validate_string(const std::string &string) {
    _fsm.setState(IdMap::start);
    size_t i = 0;
    while(i < string.size() && string[i] != ' ' && string[i] != '\t'){
        _fsm.change_state(string[i]);
        if(_fsm.getState().getName() == IdMap::error.getName())
            return false;
        ++i;
    }
    return is_valid;
}
