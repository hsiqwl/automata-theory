#ifndef INTERPRETER_PARSING_DRIVER_H
#define INTERPRETER_PARSING_DRIVER_H

#include <string>
#include <cstddef>
#include "grammar.tab.hh"
#include "ast.h"

#define YY_DECL yy::parser::symbol_type yylex (driver& drv)

YY_DECL;

class driver{
public:
    driver();

    int parse(const std::string& filename);

    [[nodiscard]] const yy::location& get_location() const;

    void set_trace_parsing(bool tracing);

    void set_trace_scanning(bool tracing);

    void move_location_line(int lines = 1);

    void move_location_column(int columns = 1);

    void location_step();

    Ast tree;
private:
    std::string file;

    bool trace_parsing;

    void scan_begin();

    void scan_end();

    bool trace_scanning;

    yy::location location;
};
#endif //! INTERPRETER_PARSING_DRIVER_H
