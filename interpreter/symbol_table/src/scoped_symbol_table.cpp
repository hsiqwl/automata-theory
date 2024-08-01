#include "scoped_symbol_table.h"

ScopedSymTable::ScopedSymTable(std::string_view scope_name, size_t scope_level)
                                         : scope_name_(scope_name), scope_level_(scope_level) {}


void ScopedSymTable::InsertSymbol(std::unique_ptr<Symbol> &&new_symbol) {
    sym_tab_.emplace(new_symbol->GetName(), std::move(new_symbol));
}

const Symbol &ScopedSymTable::GetSymbol(const std::string &name) const {
    return *(sym_tab_.find(name)->second);
}

bool ScopedSymTable::SymbolDeclared(const std::string &name) const noexcept {
    return sym_tab_.contains(name);
}

const std::string &ScopedSymTable::GetScopeName() const noexcept {
    return scope_name_;
}

size_t ScopedSymTable::GetScopeLevel() const noexcept {
    return scope_level_;
}