#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H
#include "regex_tokenizer.h"
#include "ast_builder.h"
#include "dfa_builder.h"

class regex{
public:
    regex(std::string_view expression);

    bool match(std::string_view string);

    bool match_with_nfa(std::string_view string);

    //regex get_reverse_language() const;

    [[nodiscard]] regex get_complemented_language() const;

private:
    nfa_simulator nfa;

    dfa engine;

    bool is_complemented = false;

    regex(const regex& other);
};

#endif //REGEX_REGEX_H
