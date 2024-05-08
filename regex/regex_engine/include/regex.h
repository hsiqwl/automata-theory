#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H
#include "regex_tokenizer.h"
#include "ast_builder.h"
#include "dfa_builder.h"
#include "dfa_to_regex.h"

class regex{
public:
    regex(std::string_view expression);

    regex(const regex& other) = default;

    bool match(std::string_view string);

    regex get_reverse_language() const;

    [[nodiscard]] regex get_complemented_language() const;

    std::string get_initial_regex() const noexcept;

    std::string get_capture_group(size_t number);

private:
    regex() = default;

    group_manager manager;

    dfa engine;

    bool is_complemented = false;
};

#endif //REGEX_REGEX_H
