#include <iostream>
#include <format>
#include "regex.h"

int main() {
    regex regexpr("a.bc{1,2}c?a?");
    bool result = regexpr.match("abccca");
    std::cout << std::boolalpha << std::format("string matches? -- {}\n", result);
}
