#ifndef INTERPRETER_UNSIGNED_LITERAL_H
#define INTERPRETER_UNSIGNED_LITERAL_H
#include "node_interface.h"
#include "unsigned_value.h"
#include "value.h"
#include "printable_interface.h"

class UnsignedLiteralNode: public INode, public IPrintable{
public:
    UnsignedLiteralNode(unsigned value, const location_t &loc);

    Value GetValue() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream& stream) const override;

private:
    UnsignedValue value_;
};

#endif //INTERPRETER_UNSIGNED_LITERAL_H
