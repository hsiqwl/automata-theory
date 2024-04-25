#include <iostream>
#include <format>
#include "regex.h"

int main() {
    regex regexpr("abc");
    bool result = regexpr.match("abcd");
    std::cout << std::boolalpha << std::format("string matches? -- {}\n", result);
}
