#include "cell_value.h"
#include "value.h"

CellValue::CellValue(Cell value): IValue(TypeToken::Cell), ValueHolder<Cell>(value) {}

Value CellValue::Equal(const IValue &other) const {
    throw std::logic_error("cannot apply '=' operation on Cell type");
}

Value CellValue::Less(const IValue &other) const {
    throw std::logic_error("cannot apply '<' operation on Cell type");
}

Value CellValue::Greater(const IValue &other) const {
    throw std::logic_error("cannot apply '>' operation on Cell type");
}

Value CellValue::Minus(const IValue &other) const {
    return CellValue(value_ - std::any_cast<Cell>(other.GetValue()));
}

Value CellValue::Plus(const IValue &other) const {
    throw std::logic_error("cannot apply '+' operation on Cell type");
}

Value CellValue::Star(const IValue &other) const {
    throw std::logic_error("cannot apply '*' operation on Cell type");
}

Value CellValue::Slash(const IValue &other) const {
    return CellValue(value_ / std::any_cast<Cell>(other.GetValue()));
}

Value CellValue::Percent(const IValue &other) const {
    return CellValue(value_ % std::any_cast<Cell>(other.GetValue()));
}

Value CellValue::Hash() const {
    throw std::logic_error("Cannot apply '#' operator to Signed type");
}

std::any CellValue::GetValue() const {
    return std::make_any<Cell>(value_);
}

void CellValue::SetValue(std::any &&new_value) {
    value_ = std::any_cast<Cell>(std::move(new_value));
}