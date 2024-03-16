#include "string_utilities.h"

void add_prefix_to_same_strings(std::vector<std::string>& first, std::vector<std::string>& second,
                                const std::string& first_prefix, const std::string& second_prefix) {
    for (auto &i: first) {
        for (auto &j: second) {
            if (i == j) {
                i.insert(0, first_prefix + ".");
                j.insert(0, second_prefix + ".");
            }
        }
    }
}

std::string convert_vector_to_string(const std::vector<std::string>& strings) {
    std::string result;
    for (auto &s: strings) {
        result.append(s);
        result.append(" ");
    }
    return result;
}

std::vector<std::string> split_string_by_delimiters
    (const std::string& string, const std::string& delim) {
    size_t first = 0;
    bool complete_token = false;
    std::vector<std::string> splits;
    size_t i = 0;
    for (; i < string.size(); ++i) {
        if (delim.find(string[i]) != std::string::npos) {
            if (complete_token) {
                splits.emplace_back(std::string{string.begin() + first, string.begin() + i});
                complete_token = false;
            }
        } else {
            if (!complete_token) {
                first = i;
                complete_token = true;
            }
        }
    }
    if (complete_token)
        splits.emplace_back(std::string{string.begin() + first, string.begin() + i});
    return splits;
}
