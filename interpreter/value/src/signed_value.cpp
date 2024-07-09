#include "signed_value.h"

std::any SignedValue::GetValue() const {
    return std::make_any<int>(value_);
}

void SignedValue::SetValue(std::any &&new_value) {
    value_ = std::any_cast<int>(std::move(new_value));
}

bool SignedValue::operator == (const ValueInterface &other) const {
    try {
        return value_ == std::any_cast<int>(other.GetValue());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '==' operator on incomparable types");
    }
}
bool SignedValue::operator < (const ValueInterface &other) const {
    try {
        return value_ < std::any_cast<int>(other.GetValue());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '<' operator on incomparable types");
    }
}

bool SignedValue::operator > (const ValueInterface &other) const {
    try {
        return value_ > std::any_cast<int>(other.GetValue());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '>' operator on incomparable types");
    }
}

std::unique_ptr<ValueInterface> SignedValue::operator + (const ValueInterface &other) const {
    try {
        std::unique_ptr<SignedValue> sum_value = std::make_unique<SignedValue>();
        sum_value->SetValue(std::make_any<int>(value_ + std::any_cast<int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> SignedValue::operator-(const ValueInterface &other) const {
    try {
        std::unique_ptr<SignedValue> sum_value = std::make_unique<SignedValue>();
        sum_value->SetValue(std::make_any<int>(value_ - std::any_cast<int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> SignedValue::operator*(const ValueInterface &other) const {
    try {
        std::unique_ptr<SignedValue> sum_value = std::make_unique<SignedValue>();
        sum_value->SetValue(std::make_any<int>(value_ * std::any_cast<int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> SignedValue::operator/(const ValueInterface &other) const {
    try {
        std::unique_ptr<SignedValue> sum_value = std::make_unique<SignedValue>();
        sum_value->SetValue(std::make_any<int>(value_ / std::any_cast<int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> SignedValue::operator%(const ValueInterface &other) const {
    try {
        std::unique_ptr<SignedValue> sum_value = std::make_unique<SignedValue>();
        sum_value->SetValue(std::make_any<int>(value_ % std::any_cast<int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

ValueInterface &SignedValue::operator()(size_t i, size_t j) {
    throw std::logic_error("cannot perform '()' operator on type_ of 'SignedValue'");
}

const ValueInterface &SignedValue::operator()(size_t i, size_t j) const {
    throw std::logic_error("cannot perform '()' operator on type_ of 'SignedValue'");
}

std::unique_ptr<ValueInterface> SignedValue::operator^(const ValueInterface &other) const {
    throw std::logic_error("cannot perform '^' operator on type_ of 'SignedValue'");
}