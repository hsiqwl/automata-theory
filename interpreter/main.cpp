#include <iostream>
#include "parsing_driver.h"
#include "printer.h"

int main(int argc, char *argv[]) {
    driver drv;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p"))
            drv.set_trace_parsing(true);
        else if (argv[i] == std::string("-s"))
            drv.set_trace_scanning(true);
        else if(!drv.parse(argv[i]))
            std::cout << "parsing ended\n";
    }
    auto res = drv.tree_->Evaluate();
    std::cout << res << '\n';
    return 0;

}
