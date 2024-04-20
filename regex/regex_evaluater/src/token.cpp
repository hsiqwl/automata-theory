#include "token.h"

token::token(token::token_type type): type(type), nullability(false) {}

token::token_type token::get_type() const noexcept {
    return type;
}

void token::set_nullability(bool token_nullability) {
    nullability = token_nullability;
}

void token::set_operator_info(const operator_info &info) {
    if(type == token_type::op)
        token_info.emplace<operator_info>(info);
    else
        throw std::logic_error("Token type must be token::token_type::op");
}

void token::set_terminal_info(const terminal_info &info) {
    if(type == token_type::terminal)
        token_info.emplace<terminal_info>(info);
    else
        throw std::logic_error("Token type must be token::token_type::terminal");
}

const std::vector<size_t> &token::get_first_pos() const noexcept {
    return first_pos;
}

const std::vector<size_t> &token::get_last_pos() const noexcept {
    return last_pos;
}

bool token::is_nullable() const noexcept {
    return nullability;
}

const operator_info &token::get_operator_info() const{
    return std::get<operator_info>(token_info);
}

const terminal_info &token::get_terminal_info() const{
    return std::get<terminal_info>(token_info);
}

void token::add_to_first_pos(size_t pos) {
    first_pos.push_back(pos);
}

void token::add_to_last_pos(size_t pos) {
    last_pos.push_back(pos);
}

size_t token::get_sub_expression_length() const noexcept {
    if(!last_pos.empty()){
        return *std::min_element(last_pos.begin(), last_pos.end());
    }
    return 0;
}