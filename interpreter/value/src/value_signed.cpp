#include "value_signed.h"

std::any value_signed::get_value() const {
    return std::make_any<int>(value);
}

void value_signed::set_value(std::any &&new_value) {
    value = std::any_cast<int>(std::move(new_value));
}

bool value_signed::operator == (const value_interface &other) const {
    try {
        return value == std::any_cast<int>(other.get_value());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '==' operator on incomparable types");
    }
}
bool value_signed::operator < (const value_interface &other) const {
    try {
        return value < std::any_cast<int>(other.get_value());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '<' operator on incomparable types");
    }
}

bool value_signed::operator > (const value_interface &other) const {
    try {
        return value > std::any_cast<int>(other.get_value());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '>' operator on incomparable types");
    }
}

std::unique_ptr<value_interface> value_signed::operator + (const value_interface &other) const {
    try {
        std::unique_ptr<value_signed> sum_value = std::make_unique<value_signed>();
        sum_value->set_value(std::make_any<int>(value + std::any_cast<int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_signed::operator-(const value_interface &other) const {
    try {
        std::unique_ptr<value_signed> sum_value = std::make_unique<value_signed>();
        sum_value->set_value(std::make_any<int>(value - std::any_cast<int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_signed::operator*(const value_interface &other) const {
    try {
        std::unique_ptr<value_signed> sum_value = std::make_unique<value_signed>();
        sum_value->set_value(std::make_any<int>(value * std::any_cast<int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_signed::operator/(const value_interface &other) const {
    try {
        std::unique_ptr<value_signed> sum_value = std::make_unique<value_signed>();
        sum_value->set_value(std::make_any<int>(value / std::any_cast<int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_signed::operator%(const value_interface &other) const {
    try {
        std::unique_ptr<value_signed> sum_value = std::make_unique<value_signed>();
        sum_value->set_value(std::make_any<int>(value % std::any_cast<int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

value_interface &value_signed::operator()(size_t i, size_t j) {
    throw std::logic_error("cannot perform '()' operator on type of 'value_signed'");
}

const value_interface &value_signed::operator()(size_t i, size_t j) const {
    throw std::logic_error("cannot perform '()' operator on type of 'value_signed'");
}

std::unique_ptr<value_interface> value_signed::operator^(const value_interface &other) const {
    throw std::logic_error("cannot perform '^' operator on type of 'value_signed'");
}