#include "scanner.h"
std::pair<bool, std::optional<std::string>> parser::parse(const std::string &string) {
    std::sregex_token_iterator iterator{string.begin(), string.end(), pattern, {1, 2, 3, 4}};
    std::sregex_token_iterator end;
    if (iterator == end) {
        return {false, std::nullopt};
    }
    if (string.find('(') != std::string::npos) {
        put_capture_group_info_into_table(iterator);
        return {true, std::nullopt};
    } else {
        std::advance(iterator, 2);
        return {true, extract_capture_group_info(iterator)};
    }
}

void parser::put_capture_group_info_into_table(std::sregex_token_iterator &iterator) {
    std::string key{std::move(iterator->str())};
    std::vector<std::string> capture_group_info = split_string_by_delimiters((++iterator)->str(), "\t ,");
    attributes_table.insert_or_assign(std::move(key), std::move(capture_group_info));
}

std::optional<std::string> parser::extract_capture_group_info(std::sregex_token_iterator &iterator) {
    auto first_id_note = attributes_table.find(iterator->str());
    auto second_id_note = attributes_table.find((++iterator)->str());
    auto end = attributes_table.end();
    if (first_id_note != end && second_id_note != end) {
        add_prefix_to_same_strings(first_id_note->second, second_id_note->second, first_id_note->first,
                                   second_id_note->first);
        return {convert_vector_to_string(first_id_note->second) + "\n" +
                                          convert_vector_to_string(second_id_note->second)};
    } else if (first_id_note != end) {
        return {convert_vector_to_string(first_id_note->second)};
    } else if (second_id_note != end) {
        return {convert_vector_to_string(second_id_note->second)};
    } else {
        return std::nullopt;
    }
}