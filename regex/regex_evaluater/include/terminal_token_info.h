#ifndef REGEX_TERMINAL_TOKEN_INFO_H
#define REGEX_TERMINAL_TOKEN_INFO_H
#include <string_view>
#include <vector>

struct terminal_token_info{
    enum class terminal_type{
        single_character,
        character_class
    };

    terminal_type type;

    char range_min;

    char range_max;

    std::string_view singles;

    bool is_negated;

    std::vector<size_t> starts_groups;

    std::vector<size_t> ends_groups;

    terminal_token_info(char c);

    terminal_token_info(char _range_min, char _range_max, std::string_view _singles, bool _is_negated);

    terminal_token_info(std::string_view singles, bool _is_negated);
};

#endif //REGEX_TERMINAL_TOKEN_INFO_H
