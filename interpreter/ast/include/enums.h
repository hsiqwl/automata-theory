#ifndef INTERPRETER_ENUMS_H
#define INTERPRETER_ENUMS_H

enum class node_type{
    operation,
    operand
};

enum class operation_type{
    plus,
    minus,
    star,
    slash,
    percent,
    less,
    greater,
    equal
};

enum class operand_category{
    immediate_value,
    variable
};
#endif //INTERPRETER_ENUMS_H
