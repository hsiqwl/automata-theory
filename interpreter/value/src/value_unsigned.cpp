#include "value_unsigned.h"

std::any value_unsigned::get_value() const {
    return std::make_any<unsigned int>(value);
}

void value_unsigned::set_value(std::any &&new_value) {
    value = std::any_cast<unsigned int>(std::move(new_value));
}

bool value_unsigned::operator==(const value_interface &other) const {
    try {
        return value == std::any_cast<unsigned int>(other.get_value());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '==' operator on incomparable types");
    }
}

bool value_unsigned::operator>(const value_interface &other) const {
    try {
        return value > std::any_cast<unsigned int>(other.get_value());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '>' operator on incomparable types");
    }
}

bool value_unsigned::operator<(const value_interface &other) const {
    try {
        return value < std::any_cast<unsigned int>(other.get_value());
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Using '<' operator on incomparable types");
    }
}

std::unique_ptr<value_interface> value_unsigned::operator+(const value_interface &other) const {
    try {
        std::unique_ptr<value_unsigned> sum_value = std::make_unique<value_unsigned>();
        sum_value->set_value(std::make_any<unsigned int>(value + std::any_cast<unsigned int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_unsigned::operator-(const value_interface &other) const {
    try {
        std::unique_ptr<value_unsigned> sum_value = std::make_unique<value_unsigned>();
        sum_value->set_value(std::make_any<unsigned int>(value - std::any_cast<unsigned int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_unsigned::operator*(const value_interface &other) const {
    try {
        std::unique_ptr<value_unsigned> sum_value = std::make_unique<value_unsigned>();
        sum_value->set_value(std::make_any<unsigned int>(value * std::any_cast<unsigned int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_unsigned::operator/(const value_interface &other) const {
    try {
        std::unique_ptr<value_unsigned> sum_value = std::make_unique<value_unsigned>();
        sum_value->set_value(std::make_any<unsigned int>(value / std::any_cast<unsigned int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

std::unique_ptr<value_interface> value_unsigned::operator%(const value_interface &other) const {
    try {
        std::unique_ptr<value_unsigned> sum_value = std::make_unique<value_unsigned>();
        sum_value->set_value(std::make_any<unsigned int>(value % std::any_cast<unsigned int>(other.get_value())));
        return sum_value;
    } catch (std::bad_any_cast &e) {
        throw std::logic_error("Impossible to perform summing of these types");
    }
}

value_interface &value_unsigned::operator()(size_t i, size_t j) {
    throw std::logic_error("cannot perform '()' operator on type of 'value_unsigned'");
}

const value_interface &value_unsigned::operator()(size_t i, size_t j) const {
    throw std::logic_error("cannot perform '()' operator on type of 'value_unsigned'");
}

std::unique_ptr<value_interface> value_unsigned::operator^(const value_interface &other) const {
    throw std::logic_error("cannot perform '^' operator on type of 'value_unsigned'");
}