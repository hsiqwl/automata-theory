#include <gtest/gtest.h>
#include "regex_engine.h"
int main(int argc, char* argv[]) {
    regex r1("a?aa+"); //for emails
    std::cout << r1.get_initial_regex() << '\n';
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
}