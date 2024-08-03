#ifndef INTERPRETER_SYM_TAB_MANAGER_H
#define INTERPRETER_SYM_TAB_MANAGER_H
#include "scoped_symbol_table.h"
#include <vector>
#include <algorithm>

class SymbolTableManager{
private:
    std::vector<ScopedSymTable> scopes_;

    const ScopedSymTable& GetClosestScopeForVar(const std::string& name) const;

public:
    SymbolTableManager();

    void AddNewScope(std::string_view scope_name, size_t scope_level);

    void RemoveCurrentScope();

    void InsertSymbol(VarSymbol new_var);

    void InsertSymbol(FunctionSymbol new_func);

    bool VarDeclaredInCurrentScope(const std::string& name) const noexcept;

    bool VarDeclaredInSomeScope(const std::string& name) const noexcept;

    bool FuncDeclared(const std::string& name) const noexcept;

    const VarSymbol& GetVar(const std::string& name) const;

    const FunctionSymbol& GetFunc(const std::string& name) const;

    const std::string& GetCurrentScopeName() const noexcept;

    size_t GetCurrentScopeLevel() const noexcept;
};
#endif //INTERPRETER_SYM_TAB_MANAGER_H
