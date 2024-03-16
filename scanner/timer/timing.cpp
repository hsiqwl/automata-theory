#include "scanner.h"
#include <fstream>
#include <chrono>

void timing(std::istream& data, std::ostream& output, parser& _parser){
    std::string str;
    std::chrono::nanoseconds time(0);
    size_t number_of_lines = 0;
    for(size_t j = 0; j < 50; ++j){
        number_of_lines += 20000;
        for(size_t i = 0; i < number_of_lines; ++i){
            std::getline(data, str, '\n');
            auto start = std::chrono::steady_clock::now();
            _parser.parse(str);
            auto end = std::chrono::steady_clock::now();
            time += end - start;
        }
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);
        output << number_of_lines << ' ' << ms << '\n';
    }
}