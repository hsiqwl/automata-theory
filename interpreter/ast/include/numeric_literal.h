#ifndef INTERPRETER_NUMERIC_LITERAL_H
#define INTERPRETER_NUMERIC_LITERAL_H
#include "node.h"
#include <variant>

class NumericLiteralNode: public Node{
public:
    explicit NumericLiteralNode(int value);

    explicit NumericLiteralNode(unsigned int value);

    void PrintOut(std::ostream& stream) const override;

private:
    bool is_signed_;

    std::variant<int, unsigned int> value_;
};

#endif //INTERPRETER_NUMERIC_LITERAL_H
