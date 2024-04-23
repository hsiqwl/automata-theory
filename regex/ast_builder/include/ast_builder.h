#ifndef REGEX_AST_BUILDER_H
#define REGEX_AST_BUILDER_H
#include "ast.h"
#include "regex_tokenizer.h"

std::shared_ptr<ast> tokens_to_ast(const std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>& iterators);

void operation_to_ast(const operator_info& info, std::stack<std::shared_ptr<ast>>& subtree);

void concat_to_ast(std::stack<std::shared_ptr<ast>>& subtree);

void alternative_to_ast(std::stack<std::shared_ptr<ast>>& subtree);

void star_to_ast(std::stack<std::shared_ptr<ast>>& subtree);

void terminal_to_ast(const terminal_info& info, std::stack<std::shared_ptr<ast>>& subtree);

void character_class_to_ast(const terminal_info& info, std::stack<std::shared_ptr<ast>>& subtree);

void single_character_to_ast(const terminal_info& info, std::stack<std::shared_ptr<ast>>& subtree);

#endif //REGEX_AST_BUILDER_H
