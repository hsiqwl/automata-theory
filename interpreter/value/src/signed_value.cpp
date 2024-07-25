#include "signed_value.h"
#include "value.h"

SignedValue::SignedValue(int value): IValue(TypeHolder{TypeToken::Signed}), ValueHolder<int>(value) {}

Value SignedValue::Equal(const IValue &other) const {
    if (value_ == std::any_cast<int>(other.GetValue()))
        return SignedValue(1);
    else
        return SignedValue(0);
}

Value SignedValue::Less(const IValue &other) const {
    if (value_ < std::any_cast<int>(other.GetValue()))
        return SignedValue(1);
    else
        return SignedValue(0);
}

Value SignedValue::Greater(const IValue &other) const {
    if (value_ > std::any_cast<int>(other.GetValue()))
        return SignedValue(1);
    else
        return SignedValue(0);
}

Value SignedValue::Minus(const IValue &other) const {
    return SignedValue(value_ - std::any_cast<int>(other.GetValue()));
}

Value SignedValue::Plus(const IValue &other) const {
    return SignedValue(value_ + std::any_cast<int>(other.GetValue()));
}

Value SignedValue::Star(const IValue &other) const {
    return SignedValue(value_ * std::any_cast<int>(other.GetValue()));
}

Value SignedValue::Slash(const IValue &other) const {
    return SignedValue(value_ / std::any_cast<int>(other.GetValue()));
}

Value SignedValue::Percent(const IValue &other) const {
    return SignedValue(value_ % std::any_cast<int>(other.GetValue()));
}

Value SignedValue::Hash() const {
    throw std::logic_error("Cannot apply '#' operator to Signed type");
}

std::any SignedValue::GetValue() const {
    return std::make_any<int>(value_);
}

void SignedValue::SetValue(std::any &&new_value) {
    value_ = std::any_cast<int>(std::move(new_value));
}