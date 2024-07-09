#ifndef INTERPRETER_VAR_H
#define INTERPRETER_VAR_H
#include "symbol.h"


class VarSymbol: public Symbol{
private:
    std::string type_;

    bool is_const_;

public:
    VarSymbol(std::string_view name, std::string_view type, bool is_const = false);

    const std::string& get_type() const;

    bool is_const() const;

    void print(std::ostream& stream) const override;
};


#endif //INTERPRETER_VAR_H
