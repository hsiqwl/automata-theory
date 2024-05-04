#include <iostream>
#include <format>
#include "regex.h"

int main() {
    regex regexpr("a|b");
    bool result = regexpr.match_with_nfa("b");
    std::cout << std::boolalpha << std::format("string matches? -- {}\n", result);
}