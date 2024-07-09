#include "var.h"

VarSymbol::VarSymbol(std::string_view name, std::string_view type, bool is_const)
    : Symbol(name), type_(type), is_const_(is_const) {}

bool VarSymbol::is_const() const {
    return is_const_;
}

const std::string &VarSymbol::get_type() const {
    return type_;
}

void VarSymbol::print(std::ostream &stream) const {
    stream << "====== SYMBOL ======\n";
    stream << "Symbol category: VarSymbol\n";
    stream << "name_:" << name_ << '\n';
    stream << "VarSymbol type_:" << type_ << '\n';
    stream << std::boolalpha << "is const:" << is_const_ << '\n';
    stream << "====== SYMBOL ======\n";
}