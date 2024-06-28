#include "operation_node.h"

void operation_node::set_label() {
    switch (op_type) {
        case operation_type::plus:
            label = "+";
            return;
        case operation_type::minus:
            label = "-";
            return;
        case operation_type::star:
            label = "*";
            return;
        case operation_type::slash:
            label = "/";
            return;
        case operation_type::percent:
            label = "%";
            return;
        case operation_type::less:
            label = "<";
            return;
        case operation_type::greater:
            label = ">";
            return;
        case operation_type::equal:
            label = "=";
            return;
    }
}

operation_node::operation_node(operation_type op_type, std::unique_ptr<node> &&first, std::unique_ptr<node> &&second)
    :node(node_type::operation), op_type(op_type) {
    first_operand = std::move(first);
    if (second != nullptr)
        second_operand.emplace(std::move(second));

    set_label();
}

void operation_node::print(std::ostream &stream) const {
    stream << "printing operation node with label:'" << label << "'\n";
}