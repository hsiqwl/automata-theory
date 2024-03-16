#include <iostream>
#include <fstream>
#include "scanner.h"
#include <format>
int main() {
    try {
        std::string string;
        parser _parser;
        while(std::getline(std::cin, string, '\n')){
            std::cout<<"input string:'"<<string<<"'\n";
            std::pair<bool, std::optional<std::string>> result = _parser.parse(string);
            if(result.first){
                std::cout<<std::format("string is valid\n INFO:\n {}\nEND INFO\n",
                                       (result.second.has_value() ? result.second.value() : "none"));
            }else{
                std::cout<<"string is invalid\n";
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}