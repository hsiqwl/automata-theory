#ifndef VALIDATOR_SCANNER_H
#define VALIDATOR_SCANNER_H
#include "join_scanner.h"
#include "id_scanner.h"
#include "create_scanner.h"
#include "info_collector.h"
#include "../../basic_scanner/basic_scanner.h"
#include "../../recognizer/include/recognizer.h"
#include "pattern_scanner_sm.h"
#include <memory>
class parser: public basic_scanner, public recognizer{
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

private:
    bool validate_string(const std::string& string) override;

private:
    pattern_scannerContext _fsm;
    std::vector<std::unique_ptr<basic_scanner>> scanners;
    info_collector collector;
    std::string move_string_to_next_token_start(std::string& string);

public:
    parser();
    std::pair<bool, std::optional<std::string>> parse(const std::string& string) override;
    ~parser() override;
};


#endif //VALIDATOR_SCANNER_H
