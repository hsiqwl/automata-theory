#include "sym_tab_manager.h"

#include <ranges>

SymbolTableManager::SymbolTableManager() {
    scopes_.emplace_back();
}

bool SymbolTableManager::SymbolDeclaredSomewhere(const std::string &name) {
    return std::any_of(scopes_.begin(), scopes_.end(), [&name](const ScopedSymTable& scope){
        return scope.SymbolDeclared(name);
    });
}

const ScopedSymTable &SymbolTableManager::GetClosestScope(const std::string &name) {
    for(auto & scope : std::ranges::reverse_view(scopes_)){
        if(scope.SymbolDeclared(name))
            return scope;
    }
}

void SymbolTableManager::AddNewScope(std::string_view scope_name, size_t scope_level) {
    scopes_.emplace_back(scope_name, scope_level);
}

void SymbolTableManager::RemoveCurrentScope() {
    scopes_.pop_back();
}

void SymbolTableManager::InsertSymbolToCurrentScope(std::unique_ptr<Symbol> &&symbol) {
    scopes_.back().InsertSymbol(std::move(symbol));
}

bool SymbolTableManager::SymbolDeclaredInCurrentScope(const std::string &name) {
    return scopes_.back().SymbolDeclared(name);
}

const Symbol &SymbolTableManager::GetSymbol(const std::string &name) {
    return GetClosestScope(name).GetSymbol(name);
}

const std::string &SymbolTableManager::GetCurrentScopeName() const noexcept {
    return scopes_.back().GetScopeName();
}

size_t SymbolTableManager::GetCurrentScopeLevel() const noexcept {
    return scopes_.back().GetScopeLevel();
}