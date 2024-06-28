#ifndef INTERPRETER_OPERATION_NODE_H
#define INTERPRETER_OPERATION_NODE_H
#include "node.h"
#include <optional>
#include <memory>
#include <string>

class operation_node: public node{
public:
    operation_node(operation_type op_type, std::unique_ptr<node>&& first, std::unique_ptr<node>&& second = nullptr);

    void print(std::ostream& stream) const override;

private:
    operation_type op_type;

    std::unique_ptr<node> first_operand;

    std::optional<std::unique_ptr<node>> second_operand;

    void set_label();
};

#endif //INTERPRETER_OPERATION_NODE_H
