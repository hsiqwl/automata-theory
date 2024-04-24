#include <iostream>
#include <fstream>
#include <format>
#include "ast_builder.h"
#include "dfa_builder.h"

int main() {
    std::string expr = "ab";
    regex_tokenizer tokenizer(expr);
    std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator> iterators = std::make_pair(tokenizer.get_token_sequence().begin(), tokenizer.get_token_sequence().end());
    ast tree = ast_builder::tokens_to_ast(iterators);
    dfa_builder builder(tree);
    dfa automaton = builder.build();
}
