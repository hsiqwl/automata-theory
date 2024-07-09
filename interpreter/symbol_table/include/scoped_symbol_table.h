#ifndef INTERPRETER_SCOPED_SYMBOL_TABLE_H
#define INTERPRETER_SCOPED_SYMBOL_TABLE_H
#include "symbol.h"
#include <unordered_map>
#include <memory>

class ScopedSymTable{
private:
    std::unordered_map<std::string, std::unique_ptr<Symbol>> sym_tab_;

    std::string scope_name_;

    ScopedSymTable* enclosing_scope_;

public:
    ScopedSymTable(std::string_view scope_name, ScopedSymTable* enclosing_scope);

    void InsertSymbol(std::unique_ptr<Symbol>&& new_symbol);

    bool SymbolIsDeclared(const std::string& name);

    Symbol& GetSymbol(const std::string& name);
};

#endif //INTERPRETER_SCOPED_SYMBOL_TABLE_H
