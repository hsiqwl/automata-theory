#ifndef INTERPRETER_OPERAND_NODE_H
#define INTERPRETER_OPERAND_NODE_H
#include "node.h"
#include <optional>

class operand_node: public node{
public:
    operand_node(std::string_view type);

    operand_node(std::string_view type, std::string_view var_name);

    void print(std::ostream& stream) const override;

    void accept(node_visitor& visitor) override;

private:
    operand_category category;

    std::string type;

    std::optional<std::string> var_name;
};


#endif //INTERPRETER_OPERAND_NODE_H
