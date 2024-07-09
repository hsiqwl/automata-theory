#include <iostream>
#include "parsing_driver.h"

int main(int argc, char *argv[]) {
    int res = 0;
    driver drv;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p"))
            drv.set_trace_parsing(true);
        else if (argv[i] == std::string("-s"))
            drv.set_trace_scanning(true);
        else if (!drv.parse(argv[i]))
            std::cout << "parsing ended\n";
        else
            res = 1;
    }
    return res;
}
