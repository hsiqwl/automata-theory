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
    std::shared_ptr<state> curr_state = engine.get_curr_state();
    if (curr_state == nullptr) {
        throw std::logic_error("Fatal error, empty automaton");
    }
    for (char c: string) {
        curr_state = curr_state->get_following_state(c).lock();
        if (curr_state == nullptr) {
            engine.reset();
            return false;
        }
    }
    if (curr_state->is_accepting()) {
        engine.reset();
        return true;
    }
    engine.reset();
    return false;
}

regex regex::get_complemented_language() const {
    regex result(*this);
    make_complementation(result.engine);
    return result;
}