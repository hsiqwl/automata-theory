#include <iostream>
#include <fstream>
#include <format>
#include "ast_builder.h"

int main() {
    std::string expr = "a{1,5}";
    regex_tokenizer tokenizer(expr);
    std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator> iterators = std::make_pair(tokenizer.get_token_sequence().begin(), tokenizer.get_token_sequence().end());
    std::shared_ptr<ast> tree = tokens_to_ast(iterators);
    std::function<void (const node&)> printer = [](const node& visiting_node){
        std::cout<<visiting_node.get_label()<<'\n';
    };
    ast copy = tree->get_deep_copy();
    tree->traverse(printer);
    tree.reset();
    std::cout<<"SECOND TREE\n\n\n";
    copy.traverse(printer);
}
