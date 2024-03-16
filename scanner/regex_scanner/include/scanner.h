#ifndef VALIDATOR_SCANNER_H
#define VALIDATOR_SCANNER_H
#include <regex>
#include <string>
#include <unordered_map>
#include <optional>
#include "string_utilities.h"
#include "recognizer.h"

class parser: public recognizer{
    private:
    inline const static std::regex pattern {R"(^(?:create)[ \t]+([a-z_.][\w.]*)[ \t]*\([ \t]*([a-z_.][\w.]*[ \t]*(?:,[ \t]*[a-z_.][\w.]*[ \t]*)*)\)[ \t]*$|^([a-z._][\w.]*)(?:[ ]*|[ ]+(?:join)[ ]+([a-z._][\w.]*)[ ]*)$)",
                                                  std::regex_constants::icase | std::regex_constants::optimize};
    std::unordered_map<std::string, std::vector<std::string>> attributes_table;

    std::optional<std::string> extract_capture_group_info(std::sregex_token_iterator& iterator);

    void put_capture_group_info_into_table(std::sregex_token_iterator& iterator);


    public:
    parser() = default;
    std::pair<bool, std::optional<std::string>> parse(const std::string& string) override;
};

#endif //VALIDATOR_SCANNER_H
