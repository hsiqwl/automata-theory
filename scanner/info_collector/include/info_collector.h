#ifndef VALIDATOR_INFO_COLLECTOR_H
#define VALIDATOR_INFO_COLLECTOR_H
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include "../../string_utilities/string_utilities.h"

class info_collector{
private:
    std::pair<std::string, std::vector<std::string>> accumulated_info;
    std::pair<std::string, std::string> info_args;
    std::unordered_map<std::string, std::vector<std::string>> attribute_table;

public:
    info_collector() = default;
    void remember_argument(std::string string);
    void accumulate_key_info(std::string string);
    void accumulate_arg_info(std::string string);
    void put_accumulated_info_into_table();
    void clear_info_args();
    void clear_accumulated_info();
    std::optional<std::string> get_resulting_info_string();
};


#endif //VALIDATOR_INFO_COLLECTOR_H
