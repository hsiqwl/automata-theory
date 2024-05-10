#include <iostream>
#include "regex.h"
#include "match_results.h"

int main() {
    try {
        regex re("a(bc)aspf(aksf)");
        match_result submatches(re, "a");
        for(auto& submatch: submatches){
            std::cout << submatch << '\n';
        }
    }catch (std::exception& e){
        std::cout << e.what()<<'\n';
    }
}