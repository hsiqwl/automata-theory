#include "value_cell.h"

std::any value_cell::get_value() const {
    return std::make_any<cell>(value);
}

void value_cell::set_value(std::any &&new_value) {
    value = std::any_cast<cell>(std::move(new_value));
}

bool value_cell::operator==(const value_interface &other) const {
    return value == std::any_cast<cell>(other.get_value());
}

bool value_cell::operator>(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator '>' on type cell");
}

bool value_cell::operator<(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator '<' on type cell");
}

value_interface &value_cell::operator()(size_t i, size_t j) {
    throw std::logic_error("Can't perform addressing operator '()' on type cell");
}

const value_interface &value_cell::operator()(size_t i, size_t j) const {
    throw std::logic_error("Can't perform addressing operator '()' on type cell");
}

std::unique_ptr<value_interface> value_cell::operator*(const value_interface &other) const {
    throw std::logic_error("Can't perform subtract operator '*' on type cell");
}

std::unique_ptr<value_interface> value_cell::operator+(const value_interface &other) const {
    throw std::logic_error("Can't perform summing operator '+' on type cell");
}

std::unique_ptr<value_interface> value_cell::operator-(const value_interface &other) const {
    std::unique_ptr<value_cell> new_value = std::make_unique<value_cell>();
    new_value->set_value(std::make_any<cell>(value - std::any_cast<cell>(other.get_value())));
    return new_value;
}

std::unique_ptr<value_interface> value_cell::operator/(const value_interface &other) const {
    std::unique_ptr<value_cell> new_value = std::make_unique<value_cell>();
    new_value->set_value(std::make_any<cell>(value / std::any_cast<cell>(other.get_value())));
    return new_value;
}

std::unique_ptr<value_interface> value_cell::operator%(const value_interface &other) const {
    std::unique_ptr<value_cell> new_value = std::make_unique<value_cell>();
    new_value->set_value(std::make_any<cell>(value % std::any_cast<cell>(other.get_value())));
    return new_value;
}

std::unique_ptr<value_interface> value_cell::operator^(const value_interface &other) const {
    throw std::logic_error("Can't perform operator '^' on type cell");
}
