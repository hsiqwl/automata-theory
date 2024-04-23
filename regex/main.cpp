#include <iostream>
#include <fstream>
#include <format>
#include "ast_builder.h"

int main() {
    std::string expr = "[a-c](f|d)a*bc";
    regex_tokenizer tokenizer(expr);
    std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator> iterators = std::make_pair(tokenizer.get_token_sequence().begin(), tokenizer.get_token_sequence().end());
    std::shared_ptr<ast> tree = tokens_to_ast(iterators);

}
