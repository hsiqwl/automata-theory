#ifndef VALIDATOR_SCANNER_H
#define VALIDATOR_SCANNER_H
#include <FlexLexer.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include "info_collector.h"
#include "recognizer.h"
class parser: public recognizer{
private:
    yyFlexLexer lex;
    info_collector collector;

    bool validate_string(const std::string& string);

public:
    parser() = default;

    std::pair<bool, std::optional<std::string>> parse(const std::string& string) override;
};

#endif //VALIDATOR_SCANNER_H
