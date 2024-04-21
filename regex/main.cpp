#include <iostream>
#include <format>
#include "dfa_builder.h"


int main() {
    std::string expression("(a|b)a*bb");
    dfa_builder builder;
    std::vector<std::vector<size_t>> follow_pos = builder.get_pre_build_info(expression);
    size_t i = 1;
    for(const auto& positions: follow_pos) {
        std::cout << "pos:" << i << "follow_pos:{";
        for (auto pos: positions) {
            std::cout << pos << ",";
        }
        std::cout << "}\n";
        i++;
    }
}
