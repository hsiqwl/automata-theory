#include <iostream>
//TODO: make static public method for validating the regex itself (https://www.scirp.org/html/7-8701165_21410.htm 4.3 regular expressions look for invariants)
//TODO: make constructor in which: 1)end-of-string symbol will be added 2)a method described above will be used
//TODO: MUST SEE https://www.abstractsyntaxseed.com/blog/regex-engine/introduction
//TODO: read an article on how to construct syntax tree from regex (https://www.iaeng.org/publication/WCE2012/WCE2012_pp804-809.pdf)
//TODO: construct a syntax tree from a regex represented by std::string_view

#include "regex_tokenizer.h"
#include "dfa_builder.h"

void print_token_sequence(const std::vector<std::unique_ptr<token>>& token_sequence) {
    for (auto &token: token_sequence) {
        if (token->type == token::token_type::op) {
            std::cout << "type: operation";
        } else if (token->type == token::token_type::terminal) {
            std::cout << "type: terminal";
        } else {
            std::cout << "type: parenthesis";
        }
    }
}
int main() {
    try {
        regex_tokenizer regex{"(a|b)c*"};
        print_token_sequence(dfa_builder::infix_to_postfix(regex.get_token_sequence()));
    } catch (std::exception &e) {
        std::cout << "exception: invalid regex\n";
    }
}
