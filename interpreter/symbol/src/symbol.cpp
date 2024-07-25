#include "symbol.h"

Symbol::Symbol(std::string_view name): name_(name) {}

const std::string &Symbol::GetName() const {
    return name_;
}