#include "regex.h"

regex::regex(std::string_view expression) {
    regex_tokenizer tokenizer(std::string{expression});
    std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator> iterators = std::make_pair(tokenizer.get_token_sequence().begin(), tokenizer.get_token_sequence().end());
    ast tree = ast_builder::tokens_to_ast(iterators);
    dfa_builder builder(tree);
    engine = builder.build();
}

regex::regex(const regex &other): engine(other.engine) {}

bool regex::match(std::string_view string) {
    for (char c: string) {
        engine.consume_input(c);
        if (engine.is_in_error_state()) {
            engine.reset();
            return is_complemented;
        }
    }
    engine.reset();
    return engine.is_in_accepting_state() ^ is_complemented;
}

regex regex::get_complemented_language() const {
    regex result(*this);
    result.is_complemented = true;
    return result;
}