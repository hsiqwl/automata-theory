#include <iostream>
#include <format>
#include "regex.h"

int main() {
    regex regexpr("a?a?a*a+");
    bool matches = regexpr.match("aa");
}