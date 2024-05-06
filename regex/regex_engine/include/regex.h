#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H
#include "regex_tokenizer.h"
#include "ast_builder.h"
#include "dfa_builder.h"
#include "dfa_to_regex.h"

class regex{
public:
    regex(std::string_view expression);

    regex(const regex& other);

    bool match(std::string_view string);

    bool match_with_nfa(std::string_view string);

    regex get_reverse_language() const;

    [[nodiscard]] regex get_complemented_language() const;

    std::string get_initial_regex() const noexcept;
private:
    regex() = default;

    nfa nfa_engine;

    dfa engine;

    bool is_complemented = false;
};

#endif //REGEX_REGEX_H
