#include "include/scanner.h"
#include <iostream>

int main(){
    std::string input;
    parser _parser;
    while(std::getline(std::cin,input,'\n')){
        std::cout<<"input string:'"<<input<<"'\n";
        std::pair<bool, std::optional<std::string>> parsing_result = _parser.parse(input);
        if (parsing_result.first) {
            std::cout << "string is valid\nINFO:"
                      << (parsing_result.second.has_value() ? parsing_result.second.value() : "none") << "\n\n";
        } else {
            std::cout << "string is invalid\n\n";
        }
    }
    return 0;
}