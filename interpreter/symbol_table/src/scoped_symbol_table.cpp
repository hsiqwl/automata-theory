#include "scoped_symbol_table.h"

ScopedSymTable::ScopedSymTable(std::string_view scope_name, size_t scope_level)
                                         : scope_name_(scope_name), scope_level_(scope_level) {}


void ScopedSymTable::InsertSymbol(VarSymbol new_var) {
    var_tab_.emplace(new_var.GetName(), std::move(new_var));
}

void ScopedSymTable::InsertSymbol(FunctionSymbol new_func) {
    func_tab_.emplace(new_func.GetName(), std::move(new_func));
}

bool ScopedSymTable::FuncDeclared(const std::string &name) const noexcept {
    return func_tab_.contains(name);
}

bool ScopedSymTable::VarDeclared(const std::string &name) const noexcept {
    return var_tab_.contains(name);
}

const VarSymbol &ScopedSymTable::GetVar(const std::string &name) const {
    return var_tab_.at(name);
}

const FunctionSymbol &ScopedSymTable::GetFunc(const std::string &name) const {
    return func_tab_.at(name);
}

const std::string &ScopedSymTable::GetScopeName() const noexcept {
    return scope_name_;
}

size_t ScopedSymTable::GetScopeLevel() const noexcept {
    return scope_level_;
}