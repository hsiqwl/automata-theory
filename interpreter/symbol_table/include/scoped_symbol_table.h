#ifndef INTERPRETER_SCOPED_SYMBOL_TABLE_H
#define INTERPRETER_SCOPED_SYMBOL_TABLE_H
#include "symbol.h"
#include "var.h"
#include <unordered_map>
#include <memory>

class scoped_symbol_table{
private:
    std::unordered_map<std::string, std::unique_ptr<symbol>> sym_tab;

    std::string scope_name;

    std::unique_ptr<scoped_symbol_table> enclosing_scope;

public:
    scoped_symbol_table(std::string_view scope_name, std::unique_ptr<scoped_symbol_table>&& enclosing_scope);

    void insert_symbol(std::unique_ptr<symbol>&& new_symbol);

    bool symbol_declared(const std::string& name);

    symbol& lookup(const std::string& name);
};

#endif //INTERPRETER_SCOPED_SYMBOL_TABLE_H
