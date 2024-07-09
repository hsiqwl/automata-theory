#include "cell_value.h"

std::any CellValue::GetValue() const {
    return std::make_any<Cell>(value_);
}

void CellValue::SetValue(std::any &&new_value) {
    value_ = std::any_cast<Cell>(std::move(new_value));
}

bool CellValue::operator==(const ValueInterface &other) const {
    return value_ == std::any_cast<Cell>(other.GetValue());
}

bool CellValue::operator>(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator '>' on type_ Cell");
}

bool CellValue::operator<(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator '<' on type_ Cell");
}

ValueInterface &CellValue::operator()(size_t i, size_t j) {
    throw std::logic_error("Can't perform addressing operator '()' on type_ Cell");
}

const ValueInterface &CellValue::operator()(size_t i, size_t j) const {
    throw std::logic_error("Can't perform addressing operator '()' on type_ Cell");
}

std::unique_ptr<ValueInterface> CellValue::operator*(const ValueInterface &other) const {
    throw std::logic_error("Can't perform subtract operator '*' on type_ Cell");
}

std::unique_ptr<ValueInterface> CellValue::operator+(const ValueInterface &other) const {
    throw std::logic_error("Can't perform summing operator '+' on type_ Cell");
}

std::unique_ptr<ValueInterface> CellValue::operator-(const ValueInterface &other) const {
    std::unique_ptr<CellValue> new_value = std::make_unique<CellValue>();
    new_value->SetValue(std::make_any<Cell>(value_ - std::any_cast<Cell>(other.GetValue())));
    return new_value;
}

std::unique_ptr<ValueInterface> CellValue::operator/(const ValueInterface &other) const {
    std::unique_ptr<CellValue> new_value = std::make_unique<CellValue>();
    new_value->SetValue(std::make_any<Cell>(value_ / std::any_cast<Cell>(other.GetValue())));
    return new_value;
}

std::unique_ptr<ValueInterface> CellValue::operator%(const ValueInterface &other) const {
    std::unique_ptr<CellValue> new_value = std::make_unique<CellValue>();
    new_value->SetValue(std::make_any<Cell>(value_ % std::any_cast<Cell>(other.GetValue())));
    return new_value;
}

std::unique_ptr<ValueInterface> CellValue::operator^(const ValueInterface &other) const {
    throw std::logic_error("Can't perform operator '^' on type_ Cell");
}
