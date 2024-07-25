#include "function.h"

FunctionSymbol::FunctionSymbol(std::string_view name, const TypeHolder &return_type)
    : Symbol(name), return_type_(return_type) {}

FunctionSymbol::FunctionSymbol(std::string_view name, const TypeHolder &return_type, std::vector<VarSymbol> &&params)
    : Symbol(name), return_type_(return_type), params_(std::move(params)) {}

const TypeHolderWrapper& FunctionSymbol::GetReturnType() const noexcept {
    return return_type_;
}

size_t FunctionSymbol::GetParamNumber() const noexcept{
    return params_.size();
}

const VarSymbol &FunctionSymbol::GetParamByIndex(size_t index) const {
    return params_[index];
}

void FunctionSymbol::print(std::ostream &stream) const {
    stream << "====== SYMBOL ======\n";
    stream << "Symbol category: func\n";
    stream << "func name_:" << name_ << '\n';
 //   stream << "return type_:" << return_type_ << '\n';
    stream << "FunctionSymbol params_:\n";
    for (auto &param: params_) {
        param.print(stream);
    }
    stream << "====== SYMBOL ======\n";
}
