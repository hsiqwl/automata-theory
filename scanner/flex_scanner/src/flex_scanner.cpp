#include "../include/scanner.h"
#include <iostream>
bool parser::validate_string(const std::string &string) {

    auto ss = std::istringstream(string);
    lex.yyrestart(ss);
    while(true){
        switch (lex.yylex()) {
            case 0:{
                collector.accumulate_key_info(lex.YYText());
                break;
            }
            case 1:{
                collector.remember_argument(lex.YYText());
                break;
            }
            case 2:{
                collector.accumulate_arg_info(lex.YYText());
                break;
            }
            case 3:{
                collector.put_accumulated_info_into_table();
                return true;
            }
            case 4:{
                collector.clear_accumulated_info();
                collector.clear_info_args();
                return false;
            }
        }
    }
}

std::pair<bool, std::optional<std::string>> parser::parse(const std::string &string) {
    bool string_valid = validate_string(string);
    std::optional<std::string> info_string = collector.get_resulting_info_string();
    return {string_valid, info_string};
}