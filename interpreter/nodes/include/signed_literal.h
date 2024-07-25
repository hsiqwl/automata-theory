#ifndef INTERPRETER_SIGNED_LITERAL_H
#define INTERPRETER_SIGNED_LITERAL_H
#include "node_interface.h"
#include "signed_value.h"
#include "value.h"

class SignedLiteralNode: public INode{
public:
    SignedLiteralNode(int value);

    Value GetValue() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

private:
    SignedValue value_;
};

#endif //INTERPRETER_SIGNED_LITERAL_H
