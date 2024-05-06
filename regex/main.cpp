#include <iostream>
#include <format>
#include "regex.h"

int main() {
    regex regexpr("a|bcded(ea)*");
    std::string re = regexpr.get_initial_regex();
    std::cout << re << "\n";
}