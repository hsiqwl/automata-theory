#include <iostream>
#include "regex.h"

int main() {
    try {
        regex re("a(bc)d(ef)");
        bool match = re.match("abcdef");
        std::string submatch = re.get_capture_group(1);
        std::cout << submatch << '\n';
    }catch (std::exception& e){
        std::cout << e.what()<<'\n';
    }
}