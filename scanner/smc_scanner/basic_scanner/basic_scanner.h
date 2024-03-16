#ifndef VALIDATOR_BASIC_SCANNER_H
#define VALIDATOR_BASIC_SCANNER_H
#include <string>

class MainMap_start;
class MainMap_second_command_after_first_token;
class MainMap_reading_argument_after_join_stmt;
class MainMap_finishing_second_command;
class MainMap_first_command_after_first_token;
class MainMap_first_command_after_first_argument;
class MainMap_reading_argument_list;
class MainMap_valid_argument_list;
class MainMap_finishing_first_command;
class MainMap_Default;
class MainMap_error;

class basic_scanner{
    friend class MainMap_start;
    friend class MainMap_second_command_after_first_token;
    friend class MainMap_reading_argument_after_join_stmt;
    friend class MainMap_finishing_second_command;
    friend class MainMap_first_command_after_first_token;
    friend class MainMap_first_command_after_first_argument;
    friend class MainMap_reading_argument_list;
    friend class MainMap_valid_argument_list;
    friend class MainMap_finishing_first_command;
    friend class MainMap_Default;
    friend class MainMap_error;

protected:
    bool is_valid;
    virtual bool validate_string(const std::string& string) = 0;
public:
    void validate() {is_valid = true;}
    void invalidate() {is_valid = false;}
    basic_scanner(){is_valid = false;}
};

#endif //VALIDATOR_BASIC_SCANNER_H
