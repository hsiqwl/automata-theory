#include <gtest/gtest.h>
#include "regex.h"

TEST(regex_match, dfa_based_simple_match){
    regex rgx("a");
    ASSERT_TRUE(rgx.match("a"));
    ASSERT_FALSE(rgx.match("b"));
}