#include "parsing_driver.h"
#include "grammar.tab.hh"

driver::driver()
    : trace_parsing(false), trace_scanning(false) {}

void driver::set_ast(ast &&result_tree) {
    tree = std::move(result_tree);
}

int driver::parse(const std::string &filename) {
    file = filename;
    location.initialize(&filename);
    scan_begin();
    yy::parser parser(*this);
    parser.set_debug_level(trace_parsing);
    int res = parser.parse();
    scan_end();
    return res;
}

void driver::set_trace_scanning(bool tracing) {
    trace_scanning = tracing;
}

void driver::set_trace_parsing(bool tracing) {
    trace_parsing = tracing;
}

const yy::location &driver::get_location() const {
    return location;
}

void driver::location_step() {
    location.step();
}

void driver::move_location_column(int columns) {
    location.columns(columns);
}

void driver::move_location_line(int lines) {
    location.lines(lines);
}