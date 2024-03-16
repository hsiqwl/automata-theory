#ifndef VALIDATOR_STRING_UTILITIES_H
#define VALIDATOR_STRING_UTILITIES_H
#include <string>
#include <vector>

void add_prefix_to_same_strings(std::vector<std::string>& first, std::vector<std::string>& second,
                                const std::string& first_prefix, const std::string& second_prefix);

std::string convert_vector_to_string(const std::vector<std::string>& strings);

std::vector<std::string> split_string_by_delimiters(const std::string& string, const std::string& delim);

#endif //VALIDATOR_STRING_UTILITIES_H
