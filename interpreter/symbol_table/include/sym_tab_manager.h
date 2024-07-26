#ifndef INTERPRETER_SYM_TAB_MANAGER_H
#define INTERPRETER_SYM_TAB_MANAGER_H
#include "scoped_symbol_table.h"
#include <vector>
#include <algorithm>

class SymbolTableManager{
private:
    std::vector<ScopedSymTable> scopes_;

    const ScopedSymTable& GetClosestScope(const std::string& name);

public:
    SymbolTableManager();

    void AddNewScope(std::string_view scope_name);

    void RemoveCurrentScope();

    void InsertSymbolToCurrentScope(std::unique_ptr<Symbol>&& symbol);

    bool SymbolDeclaredSomewhere(const std::string& name);

    bool SymbolDeclaredInCurrentScope(const std::string& name);

    const Symbol& GetSymbol(const std::string& name);

    const std::string& GetCurrentScopeName() const noexcept;
};
#endif //INTERPRETER_SYM_TAB_MANAGER_H
