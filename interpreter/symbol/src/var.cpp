#include "var.h"

VarSymbol::VarSymbol(std::string_view name, const TypeHolder &type, bool is_const)
    : Symbol(name), type_(type), const_qualifier_(is_const) {}

bool VarSymbol::IsConst() const {
    return const_qualifier_;
}

const TypeHolderWrapper& VarSymbol::GetType() const {
    return type_;
}

void VarSymbol::print(std::ostream &stream) const {
    stream << "====== SYMBOL ======\n";
    stream << "Symbol category: VarSymbol\n";
    stream << "name_:" << name_ << '\n';
    //stream << "VarSymbol type_:" << type_ << '\n';
    stream << std::boolalpha << "is const:" << const_qualifier_ << '\n';
    stream << "====== SYMBOL ======\n";
}