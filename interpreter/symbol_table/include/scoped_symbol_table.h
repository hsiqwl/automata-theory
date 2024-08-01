#ifndef INTERPRETER_SCOPED_SYMBOL_TABLE_H
#define INTERPRETER_SCOPED_SYMBOL_TABLE_H
#include "symbol.h"
#include <unordered_map>
#include <functional>
#include <memory>

class ScopedSymTable{
private:
    std::unordered_map<std::string, std::unique_ptr<Symbol>> sym_tab_;

    std::string scope_name_;

    size_t scope_level_;

public:
    ScopedSymTable(std::string_view scope_name = "Global Scope", size_t scope_level = 1);

    void InsertSymbol(std::unique_ptr<Symbol>&& new_symbol);

    bool SymbolDeclared(const std::string& name) const noexcept;

    const Symbol & GetSymbol(const std::string& name) const;

    const std::string& GetScopeName() const noexcept;

    size_t GetScopeLevel() const noexcept;
};

#endif //INTERPRETER_SCOPED_SYMBOL_TABLE_H
