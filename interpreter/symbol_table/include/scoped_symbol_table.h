#ifndef INTERPRETER_SCOPED_SYMBOL_TABLE_H
#define INTERPRETER_SCOPED_SYMBOL_TABLE_H
#include "var.h"
#include "function.h"
#include <unordered_map>
#include <functional>
#include <memory>

class ScopedSymTable{
private:
    std::unordered_map<std::string, VarSymbol> var_tab_;

    std::unordered_map<std::string, FunctionSymbol> func_tab_;

    std::string scope_name_;

    size_t scope_level_;

public:
    ScopedSymTable(std::string_view scope_name = "Global Scope", size_t scope_level = 1);

    void InsertSymbol(VarSymbol new_var);

    void InsertSymbol(FunctionSymbol new_func);

    bool VarDeclared(const std::string& name) const noexcept;

    bool FuncDeclared(const std::string& name) const noexcept;

    const VarSymbol& GetVar(const std::string& name) const;

    const FunctionSymbol& GetFunc(const std::string& name) const;

    const std::string& GetScopeName() const noexcept;

    size_t GetScopeLevel() const noexcept;
};

#endif //INTERPRETER_SCOPED_SYMBOL_TABLE_H
