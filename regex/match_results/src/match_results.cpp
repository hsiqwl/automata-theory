#include "match_results.h"

match_result::iterator match_result::begin() {
    return {submatch.begin()};
}

match_result::iterator match_result::end() {
    return {submatch.end()};
}

match_result::const_iterator match_result::cend() {
    return {submatch.cend()};
}

match_result::const_iterator match_result::cbegin() {
    return {submatch.cbegin()};
}

std::string &match_result::operator [] (int index) {
    return submatch[index];
}

const std::string &match_result::operator [] (int index) const {
    return submatch[index];
}

match_result::match_result(regex &executor, std::string_view string) {
    if (executor.match(string)) {
        submatch.resize(executor.manager.groups.size());
        for (auto &iter: executor.manager.groups) {
            submatch[iter.first] = iter.second.get_substring();
        }
    }
}
