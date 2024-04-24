#include <iostream>
#include <fstream>
#include <format>
#include "ast_builder.h"

int main() {
    std::string expr = "a?";
    regex_tokenizer tokenizer(expr);
    std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator> iterators = std::make_pair(tokenizer.get_token_sequence().begin(), tokenizer.get_token_sequence().end());
    ast tree = ast_builder::tokens_to_ast(iterators);
    std::function<void (const node&)> printer = [](const node& visiting_node){
        std::cout<<visiting_node.get_label()<<'\n';
    };
    ast copy = tree.get_deep_copy();
    tree.traverse(printer);
    std::cout<<"SECOND TREE\n\n\n";
    copy.traverse(printer);
}
