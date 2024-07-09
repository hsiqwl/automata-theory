#include "unsigned_value.h"

std::any UnsignedValue::GetValue() const {
    return std::make_any<unsigned int>(value_);
}

void UnsignedValue::SetValue(std::any &&new_value) {
    value_ = std::any_cast<unsigned int>(std::move(new_value));
}

bool UnsignedValue::operator==(const ValueInterface &other) const {
    try {
        return value_ == std::any_cast<unsigned int>(other.GetValue());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '==' operator on incomparable types");
    }
}

bool UnsignedValue::operator>(const ValueInterface &other) const {
    try {
        return value_ > std::any_cast<unsigned int>(other.GetValue());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '>' operator on incomparable types");
    }
}

bool UnsignedValue::operator<(const ValueInterface &other) const {
    try {
        return value_ < std::any_cast<unsigned int>(other.GetValue());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '<' operator on incomparable types");
    }
}

std::unique_ptr<ValueInterface> UnsignedValue::operator+(const ValueInterface &other) const {
    try {
        std::unique_ptr<UnsignedValue> sum_value = std::make_unique<UnsignedValue>();
        sum_value->SetValue(std::make_any<unsigned int>(value_ + std::any_cast<unsigned int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> UnsignedValue::operator-(const ValueInterface &other) const {
    try {
        std::unique_ptr<UnsignedValue> sum_value = std::make_unique<UnsignedValue>();
        sum_value->SetValue(std::make_any<unsigned int>(value_ - std::any_cast<unsigned int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> UnsignedValue::operator*(const ValueInterface &other) const {
    try {
        std::unique_ptr<UnsignedValue> sum_value = std::make_unique<UnsignedValue>();
        sum_value->SetValue(std::make_any<unsigned int>(value_ * std::any_cast<unsigned int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> UnsignedValue::operator/(const ValueInterface &other) const {
    try {
        std::unique_ptr<UnsignedValue> sum_value = std::make_unique<UnsignedValue>();
        sum_value->SetValue(std::make_any<unsigned int>(value_ / std::any_cast<unsigned int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<ValueInterface> UnsignedValue::operator%(const ValueInterface &other) const {
    try {
        std::unique_ptr<UnsignedValue> sum_value = std::make_unique<UnsignedValue>();
        sum_value->SetValue(std::make_any<unsigned int>(value_ % std::any_cast<unsigned int>(other.GetValue())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

ValueInterface &UnsignedValue::operator()(size_t i, size_t j) {
    throw std::logic_error("cannot perform '()' operator on type_ of 'UnsignedValue'");
}

const ValueInterface &UnsignedValue::operator()(size_t i, size_t j) const {
    throw std::logic_error("cannot perform '()' operator on type_ of 'UnsignedValue'");
}

std::unique_ptr<ValueInterface> UnsignedValue::operator^(const ValueInterface &other) const {
    throw std::logic_error("cannot perform '^' operator on type_ of 'UnsignedValue'");
}