#include "function.h"

function::function(std::string_view name, std::string_view return_type)
    : symbol(name), return_type(return_type) {}

function::function(std::string_view name, std::string_view return_type, std::vector<var> &&params)
    : symbol(name), return_type(return_type), params(std::move(params)) {}

const std::string &function::get_return_type() const {
    return return_type;
}

size_t function::get_param_number() const {
    return params.size();
}

const var &function::operator[](int index) const {
    return params[index];
}

void function::print(std::ostream &stream) const {
    stream << "====== SYMBOL ======\n";
    stream << "symbol category: func\n";
    stream << "func name:" << name << '\n';
    stream << "return type:" << return_type << '\n';
    stream << "function params:\n";
    for (auto &param: params) {
        param.print(stream);
    }
    stream << "====== SYMBOL ======\n";
}

