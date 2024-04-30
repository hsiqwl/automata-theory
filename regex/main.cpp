#include <iostream>
#include <format>
#include "regex.h"

int main() {
    regex regexpr("a*");
    bool result = regexpr.match("aaaaa");
    std::cout << std::boolalpha << std::format("string matches? -- {}\n", result);
    {
        regex copy = regexpr.get_complemented_language();
        result = copy.match("b");
        std::cout << std::boolalpha << std::format("string matches? -- {}\n", result);
    }
}