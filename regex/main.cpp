#include <iostream>
#include "regex.h"

int main() {
    ///(a|b?){2,3} - doesn't match anything in g1 against string "aa", but that may be right( regex101 does the same)
    /// capturing with + makes it completely greedy, matching everything it can
    try {
        regex re("(a|b?){2,3}");
        bool match = re.match("aa");
        std::string submatch = re.get_capture_group(1);
        std::cout << submatch << '\n';
        submatch = re.get_capture_group(0);
        std::cout << submatch << '\n';
    }catch (std::exception& e){
        std::cout << e.what()<<'\n';
    }
}