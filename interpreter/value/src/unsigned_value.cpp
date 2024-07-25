#include "unsigned_value.h"
#include "value.h"

UnsignedValue::UnsignedValue(unsigned value): IValue(TypeHolder{TypeToken::Unsigned}), ValueHolder<unsigned>(value) {}

Value UnsignedValue::Equal(const IValue &other) const {
    if (value_ == std::any_cast<unsigned >(other.GetValue()))
        return UnsignedValue(1);
    else
        return UnsignedValue(0);
}

Value UnsignedValue::Less(const IValue &other) const {
    if (value_ < std::any_cast<unsigned >(other.GetValue()))
        return UnsignedValue(1);
    else
        return UnsignedValue(0);
}

Value UnsignedValue::Greater(const IValue &other) const {
    if (value_ > std::any_cast<unsigned >(other.GetValue()))
        return UnsignedValue(1);
    else
        return UnsignedValue(0);
}

Value UnsignedValue::Minus(const IValue &other) const {
    return UnsignedValue(value_ - std::any_cast<unsigned >(other.GetValue()));
}

Value UnsignedValue::Plus(const IValue &other) const {
    return UnsignedValue(value_ + std::any_cast<unsigned >(other.GetValue()));
}

Value UnsignedValue::Star(const IValue &other) const {
    return UnsignedValue(value_ * std::any_cast<unsigned >(other.GetValue()));
}

Value UnsignedValue::Slash(const IValue &other) const {
    return UnsignedValue(value_ / std::any_cast<unsigned >(other.GetValue()));
}

Value UnsignedValue::Percent(const IValue &other) const {
    return UnsignedValue(value_ % std::any_cast<unsigned >(other.GetValue()));
}

Value UnsignedValue::Hash() const {
    throw std::logic_error("Cannot apply '#' operator to Unsigned type");
}

std::any UnsignedValue::GetValue() const {
    return std::make_any<unsigned >(value_);
}

void UnsignedValue::SetValue(std::any &&new_value) {
    value_ = std::any_cast<unsigned >(std::move(new_value));
}