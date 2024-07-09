#include "operand_node.h"

operand_node::operand_node(std::string_view type)
    : node(node_type::operand), category(operand_category::immediate_value), type(type) {
    label = "immediate value_";
}

operand_node::operand_node(std::string_view type, std::string_view var_name)
    : node(node_type::operand), category(operand_category::variable), type(type), var_name(var_name) {
    label = "variable:" + this->var_name.value();
}

void operand_node::print(std::ostream &stream) const {
    stream << "visiting operand, " << label << '\n';
}

void operand_node::accept(node_visitor &visitor) {
    visito
}