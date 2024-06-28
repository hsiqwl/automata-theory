#include "var.h"

var::var(std::string_view name, std::string_view type, bool is_const)
    : symbol(name), type(type), const_q(is_const) {}

bool var::is_const() const {
    return const_q;
}

const std::string &var::get_type() const {
    return type;
}

void var::print(std::ostream &stream) const {
    stream << "====== SYMBOL ======\n";
    stream << "symbol category: var\n";
    stream << "name:" << name << '\n';
    stream << "var type:" << type << '\n';
    stream << std::boolalpha << "is const:" << const_q << '\n';
    stream << "====== SYMBOL ======\n";
}