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
        switch (token->type) {
            case token::token_type::terminal: {
                auto &term_token = dynamic_cast<const single_character &>(*token);
                std::cout << "'type: terminal, " << "value:" << term_token.value << "' ";
                break;
            }
            case token::token_type::op: {
                auto &op_token = dynamic_cast<const operator_token &>(*token);
                switch (op_token.type) {
                    case operator_token::operator_type::repetition: {
                        std::cout << "'type: operation, value: * or + or ? or {}' ";
                        break;
                    }
                    case operator_token::operator_type::alternation: {
                        std::cout << "'type: operation, value: |' ";
                        break;
                    }
                    case operator_token::operator_type::concatenation: {
                        std::cout << "'type: operation, value .' ";
                        break;
                    }
                }
                break;
            }
            default: {
                std::cout << "'unknown token' ";
                break;
            }
        }
    }
}

int main() {
    try {
        regex_tokenizer regex{"(a|b)[a-c]"};
        print_token_sequence(dfa_builder::infix_to_postfix(regex.get_token_sequence()));
        std::cout<<'\n';
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}
