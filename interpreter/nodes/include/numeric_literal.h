#ifndef INTERPRETER_NUMERIC_LITERAL_H
#define INTERPRETER_NUMERIC_LITERAL_H
#include "node_interface.h"
#include <variant>

class NumericLiteralNode: public INode{
public:
    explicit NumericLiteralNode(int value);

    explicit NumericLiteralNode(unsigned int value);

    void Accept(NodeVisitor& visitor) const override;

    long GetValue() const;

private:
    bool is_signed_;

    std::variant<int, unsigned int> value_;
};

#endif //INTERPRETER_NUMERIC_LITERAL_H
