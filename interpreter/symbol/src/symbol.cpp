#include "symbol.h"

Symbol::Symbol(std::string_view name): name_(name) {}

const std::string &Symbol::get_name() const {
    return name_;
}