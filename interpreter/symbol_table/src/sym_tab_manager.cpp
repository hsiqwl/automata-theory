#include "sym_tab_manager.h"

#include <ranges>
#include <iostream>

SymbolTableManager::SymbolTableManager() {
    scopes_.emplace_back();
}

void SymbolTableManager::AddNewScope(std::string_view scope_name, size_t scope_level) {
    std::cout << "ENTERING NEW SCOPE: scope_name =" << scope_name << " scope_level =" << scope_level << '\n';
    scopes_.emplace_back(scope_name, scope_level);
}

void SymbolTableManager::RemoveCurrentScope() {
    std::cout << "EXITING SCOPE: scope_name = " << scopes_.back().GetScopeName() << '\n';
    scopes_.pop_back();
}

const ScopedSymTable &SymbolTableManager::GetClosestScopeForVar(const std::string &name) const {
    for(const auto & scope : std::ranges::reverse_view(scopes_)){
        if(scope.VarDeclared(name))
            return scope;
    }
}

const VarSymbol &SymbolTableManager::GetVar(const std::string &name) const {
    return GetClosestScopeForVar(name).GetVar(name);
}

const FunctionSymbol &SymbolTableManager::GetFunc(const std::string &name) const {
    scopes_.front().GetFunc(name);
}

void SymbolTableManager::InsertSymbol(VarSymbol new_var) {
    scopes_.back().InsertSymbol(std::move(new_var));
}

void SymbolTableManager::InsertSymbol(FunctionSymbol new_func) {
    scopes_.front().InsertSymbol(std::move(new_func));
}

bool SymbolTableManager::VarDeclaredInCurrentScope(const std::string &name) const noexcept {
    return scopes_.back().VarDeclared(name);
}

bool SymbolTableManager::VarDeclaredInSomeScope(const std::string &name) const noexcept {
    return std::any_of(scopes_.rbegin(), scopes_.rend(),
                       [&name](const ScopedSymTable &scope) { return scope.VarDeclared(name); });
}

bool SymbolTableManager::FuncDeclared(const std::string &name) const noexcept {
    return scopes_.front().FuncDeclared(name);
}

const std::string &SymbolTableManager::GetCurrentScopeName() const noexcept {
    return scopes_.back().GetScopeName();
}

size_t SymbolTableManager::GetCurrentScopeLevel() const noexcept {
    return scopes_.back().GetScopeLevel();
}