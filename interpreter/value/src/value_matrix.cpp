#include "value_matrix.h"

std::any value_matrix::get_value() const {
    return std::make_any<matrix>(value);
}

void value_matrix::set_value(std::any &&new_value) {
    value = std::move(std::any_cast<matrix>(std::move(new_value)));
}

bool value_matrix::contains_numeric_values() const {
    void *ptr = dynamic_cast<value_signed *>(&(*value[0][0]));
    if (ptr == nullptr) {
        ptr = dynamic_cast<value_signed *>(&(*value[0][0]));
        if (ptr == nullptr)
            return false;
        return true;
    }
    return true;
}

bool value_matrix::contains_cell_values() const {
    void *ptr = dynamic_cast<value_cell *>(&(*value[0][0]));
    if (ptr == nullptr)
        return false;
    return true;
}

int value_matrix::compute_average() const {
    int average = 0;
    for (auto &line: value) {
        for (auto &column: line) {
            average += std::any_cast<int>(column->get_value());
        }
    }
    return average;
}

void value_matrix::set_value_for_whole_matrix(std::any &&new_value) {
    for (auto &line: value) {
        for (auto &column: line) {
            column->set_value(std::move(new_value));
        }
    }
}

bool value_matrix::operator==(const value_interface &other) const {
    try {
        auto &other_matrix = dynamic_cast<const value_matrix &>(other);
        return value == other_matrix.value;
    } catch (std::bad_cast &e) {
        throw std::logic_error("Can't perform comparing operator on different types");
    }
}

std::unique_ptr<value_interface> value_matrix::operator^(const value_interface &other) const {
    std::unique_ptr<value_matrix> new_value = std::make_unique<value_matrix>();
    matrix new_matrix{value.size(), {value[0].size(), nullptr}};
    if(contains_cell_values()){
        
    } else if(contains_numeric_values()){
        int average = compute_average();
        new_value->set_value(std::make_any<matrix>(std::move(new_matrix)));
        new_value->set_value_for_whole_matrix(std::make_any<int>(average));
    } else
        throw std::logic_error("Can't perform '^' operator with non-numeric or non-cell type values in matrix");
}

value_interface &value_matrix::operator()(size_t i, size_t j) {
    return *value[i][j];
}

const value_interface &value_matrix::operator()(size_t i, size_t j) const {
    return *value[i][j];
}

std::unique_ptr<value_interface> value_matrix::operator*(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<value_interface> value_matrix::operator/(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<value_interface> value_matrix::operator%(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

bool value_matrix::operator<(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

bool value_matrix::operator>(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<value_interface> value_matrix::operator+(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<value_interface> value_matrix::operator-(const value_interface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}