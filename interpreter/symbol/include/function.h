#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H
#include "var.h"
#include <vector>

class FunctionSymbol: public Symbol{
private:
    std::vector<VarSymbol> params_;

    std::string return_type_;

public:
    FunctionSymbol(std::string_view name, std::string_view return_type);

    FunctionSymbol(std::string_view name, std::string_view return_type, std::vector<VarSymbol>&& params);

    size_t get_param_number() const;

    const std::string& get_return_type() const;

    const VarSymbol& operator [] (int index) const;

    void print(std::ostream& stream) const override;
};

#endif //INTERPRETER_FUNCTION_H
