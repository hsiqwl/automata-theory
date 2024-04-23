#include "ast_builder.h"

std::shared_ptr<ast> tokens_to_ast(const std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>& iterators){
    std::stack<std::shared_ptr<ast>> subtree;
    for(auto iter = iterators.first; iter < iterators.second; ++iter){
        if(iter->get_type() == token::token_type::terminal)
            terminal_to_ast(iter->get_terminal_info(), subtree);
        else
            operation_to_ast(iter->get_operator_info(), subtree);
    }
    return subtree.top();
}

void operation_to_ast(const operator_info& info, std::stack<std::shared_ptr<ast>>& subtree) {
    switch (info.get_op_type()) {
        case operator_info::operator_type::concatenation: {
            concat_to_ast(subtree);
            break;
        }
        case operator_info::operator_type::alternation: {
            alternative_to_ast(subtree);
            break;
        }
        case operator_info::operator_type::repetition: {
            star_to_ast(subtree);
            break;
        }
    }
}

void concat_to_ast(std::stack<std::shared_ptr<ast>>& subtree){
    std::shared_ptr<ast> right = subtree.top();
    subtree.pop();
    std::shared_ptr<ast> left = subtree.top();
    subtree.pop();
    subtree.emplace(std::make_shared<ast>(node::node_type::concat, *left, *right));
}

void alternative_to_ast(std::stack<std::shared_ptr<ast>>& subtree){
    std::shared_ptr<ast> right = subtree.top();
    subtree.pop();
    std::shared_ptr<ast> left = subtree.top();
    subtree.pop();
    subtree.emplace(std::make_shared<ast>(node::node_type::alternation, *left, *right));
}

void star_to_ast(std::stack<std::shared_ptr<ast>>& subtree){
    std::shared_ptr<ast> sub_tree = subtree.top();
    subtree.pop();
    subtree.emplace(std::make_shared<ast>(node::node_type::star, *sub_tree));
}

void terminal_to_ast(const terminal_info& info, std::stack<std::shared_ptr<ast>>& subtree) {
    if (info.is_character_class()) {
        character_class_to_ast(info, subtree);
    } else {
        single_character_to_ast(info, subtree);
    }
}

void single_character_to_ast(const terminal_info& info, std::stack<std::shared_ptr<ast>>& subtree){
    std::shared_ptr<node> root = std::make_shared<node>(info.get_range_min());
    subtree.emplace(std::make_shared<ast>(root));
}

void character_class_to_ast(const terminal_info& info, std::stack<std::shared_ptr<ast>>& subtree) {
    std::shared_ptr<node> root = std::make_shared<node>(info.get_range_min());
    std::shared_ptr<ast> tree = std::make_shared<ast>(root);
    size_t start = (size_t) info.get_range_min() + 1;
    size_t end = (size_t) info.get_range_max();
    for (; start <= end; ++start) {
        root = std::make_shared<node>((char) start);
        std::shared_ptr<ast> tree_from_curr_root = std::make_shared<ast>(root);
        tree = std::make_shared<ast>(node::node_type::alternation, *tree, *tree_from_curr_root);
    }
    for (char c: info.get_singles()) {
        root = std::make_shared<node>(c);
        std::shared_ptr<ast> tree_from_curr_root = std::make_shared<ast>(root);
        tree = std::make_shared<ast>(node::node_type::alternation, *tree, *tree_from_curr_root);
    }
    subtree.push(tree);
}