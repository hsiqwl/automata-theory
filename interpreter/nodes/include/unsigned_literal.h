#ifndef INTERPRETER_UNSIGNED_LITERAL_H
#define INTERPRETER_UNSIGNED_LITERAL_H
#include "node_interface.h"
#include "unsigned_value.h"
#include "value.h"


class UnsignedLiteralNode: public INode {
    UnsignedLiteralNode(unsigned value);

    Value GetValue() const noexcept;

    void Accept(NodeVisitor& visitor) const override;
private:
    UnsignedValue value_;
};

#endif //INTERPRETER_UNSIGNED_LITERAL_H
