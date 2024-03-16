#include "../include/create_scanner.h"

bool create_scanner::validate_string(const std::string &string) {
    _fsm.setState(CreateMap::start);
    size_t i = 0;
    while(string[i] != ' ' && string[i] != '\t' && i < string.size()){
        _fsm.change_state(string[i]);
        if(_fsm.getState().getId() == CreateMap::error.getId())
            return false;
        ++i;
    }
    return is_valid;
}
