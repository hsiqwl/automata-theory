#include "scoped_symbol_table.h"

ScopedSymTable::ScopedSymTable(std::string_view scope_name,
                               ScopedSymTable* enclosing_scope)
                                         : scope_name_(scope_name), enclosing_scope_(enclosing_scope){}

bool ScopedSymTable::SymbolIsDeclared(const std::string &name) {
    return sym_tab_.contains(name);
}

void ScopedSymTable::InsertSymbol(std::unique_ptr<Symbol> &&new_symbol) {
    sym_tab_.emplace(new_symbol->GetName(), std::move(new_symbol));
}

Symbol &ScopedSymTable::GetSymbol(const std::string &name) {
    return *sym_tab_[name];
}