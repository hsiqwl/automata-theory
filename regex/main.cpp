#include <iostream>
#include "regex.h"

int main() {

    /// capturing with + makes it completely greedy, matching everything it can
    try {
        regex re("a+a+a+");
        bool match = re.match("aaaa");
        std::string submatch = re.get_capture_group(1);
        std::cout << submatch << '\n';
        submatch = re.get_capture_group(2);
        std::cout << submatch << '\n';
    }catch (std::exception& e){
        std::cout << e.what()<<'\n';
    }
}