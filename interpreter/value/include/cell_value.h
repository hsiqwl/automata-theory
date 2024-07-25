#ifndef INTERPRETER_CELL_VALUE_H
#define INTERPRETER_CELL_VALUE_H
#include "value_holder.h"
#include "value_interface.h"
#include "unsigned_value.h"
#include "cell.h"

class CellValue: public IValue, public ValueHolder<Cell> {
public:
    CellValue(Cell value);

    Value Equal(const IValue &other) const override;

    Value Less(const IValue &other) const override;

    Value Greater(const IValue &other) const override;

    Value Plus(const IValue &other) const override;

    Value Minus(const IValue &other) const override;

    Value Star(const IValue &other) const override;

    Value Slash(const IValue &other) const override;

    Value Percent(const IValue &other) const override;

    Value Hash() const override;

    void SetValue(std::any &&new_value) override;

    [[nodiscard]] std::any GetValue() const override;
};
#endif //INTERPRETER_CELL_VALUE_H
