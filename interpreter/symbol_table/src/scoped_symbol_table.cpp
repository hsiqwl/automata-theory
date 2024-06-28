#include "scoped_symbol_table.h"

scoped_symbol_table::scoped_symbol_table(std::string_view scope_name,
                                         std::unique_ptr<scoped_symbol_table> &&enclosing_scope)
                                         : scope_name(scope_name), enclosing_scope(std::move(enclosing_scope)){}

bool scoped_symbol_table::symbol_declared(const std::string &name) {
    return sym_tab.contains(name);
}

void scoped_symbol_table::insert_symbol(std::unique_ptr<symbol> &&new_symbol) {
    sym_tab.emplace(new_symbol->get_name(), std::move(new_symbol));
}

symbol &scoped_symbol_table::lookup(const std::string &name) {
    return *sym_tab[name];
}