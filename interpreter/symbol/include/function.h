#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H
#include "var.h"
#include <vector>

class FunctionSymbol: public Symbol{
private:
    std::vector<VarSymbol> params_;

    TypeHolderWrapper return_type_;

public:
    FunctionSymbol(std::string_view name, const TypeHolder &return_type);

    FunctionSymbol(std::string_view name, const TypeHolder &return_type, std::vector<VarSymbol>&& params);

    size_t GetParamNumber() const noexcept;

    const TypeHolderWrapper& GetReturnType() const noexcept;

    const VarSymbol& GetParamByIndex(size_t index) const;

    void print(std::ostream& stream) const override;
};

#endif //INTERPRETER_FUNCTION_H
