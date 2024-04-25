#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H
#include "regex_tokenizer.h"
#include "ast_builder.h"
#include "dfa_builder.h"

class regex{
public:
    regex(std::string_view expression);

    bool match(std::string_view string);


private:
    dfa engine;
};

#endif //REGEX_REGEX_H
