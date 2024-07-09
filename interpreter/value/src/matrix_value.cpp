#include "matrix_value.h"

std::any MatrixValue::GetValue() const {
    return std::make_any<matrix_t>(value_);
}

void MatrixValue::SetValue(std::any &&new_value) {
    value_ = std::move(std::any_cast<matrix_t>(std::move(new_value)));
}

bool MatrixValue::contains_numeric_values() const {
    void *ptr = dynamic_cast<SignedValue *>(&(*value_[0][0]));
    if (ptr == nullptr) {
        ptr = dynamic_cast<UnsignedValue *>(&(*value_[0][0]));
        if (ptr == nullptr)
            return false;
        return true;
    }
    return true;
}

bool MatrixValue::contains_cell_values() const {
    void *ptr = dynamic_cast<CellValue *>(&(*value_[0][0]));
    if (ptr == nullptr)
        return false;
    return true;
}

int MatrixValue::compute_average() const {
    int average = 0;
    for (auto &line: value_) {
        for (auto &column: line) {
            average += std::any_cast<int>(column->GetValue());
        }
    }
    return average;
}

void MatrixValue::set_value_for_whole_matrix(std::any &&new_value) {
    for (auto &line: value_) {
        for (auto &column: line) {
            column->SetValue(std::move(new_value));
        }
    }
}

bool MatrixValue::operator==(const ValueInterface &other) const {
    auto &other_matrix = dynamic_cast<const MatrixValue &>(other);
    return value_ == other_matrix.value_;
}

std::unique_ptr<ValueInterface> MatrixValue::operator^(const ValueInterface &other) const {
    std::unique_ptr<MatrixValue> new_value = std::make_unique<MatrixValue>();
    matrix_t new_matrix{value_.size(), {value_[0].size(), nullptr}};
    if (contains_cell_values()) {

    } else if (contains_numeric_values()) {
        int average = compute_average();
        new_value->SetValue(std::make_any<matrix_t>(std::move(new_matrix)));
        new_value->set_value_for_whole_matrix(std::make_any<int>(average));
    } else
        throw std::logic_error("Can't perform '^' operator with non-numeric or non-Cell type_ values in matrix_t");
}

ValueInterface &MatrixValue::operator()(size_t i, size_t j) {
    return *value_[i][j];
}

const ValueInterface &MatrixValue::operator()(size_t i, size_t j) const {
    return *value_[i][j];
}

std::unique_ptr<ValueInterface> MatrixValue::operator*(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<ValueInterface> MatrixValue::operator/(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<ValueInterface> MatrixValue::operator%(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

bool MatrixValue::operator<(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

bool MatrixValue::operator>(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<ValueInterface> MatrixValue::operator+(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}

std::unique_ptr<ValueInterface> MatrixValue::operator-(const ValueInterface &other) const {
    throw std::logic_error("Can't perform comparing operator on different types");
}