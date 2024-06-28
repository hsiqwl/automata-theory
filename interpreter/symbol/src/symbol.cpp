#include "symbol.h"

symbol::symbol(std::string_view name): name(name) {}

const std::string &symbol::get_name() const {
    return name;
}