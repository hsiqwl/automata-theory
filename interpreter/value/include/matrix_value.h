#ifndef INTERPRETER_MATRIX_VALUE_H
#define INTERPRETER_MATRIX_VALUE_H
#include "value_interface.h"
#include "signed_value.h"
#include "unsigned_value.h"
#include "cell_value.h"
#include <vector>

class MatrixValue: public ValueInterface{
public:
    typedef std::vector<std::vector<std::shared_ptr<ValueInterface>>> matrix_t;

private:
    matrix_t value_;

    [[nodiscard]] bool contains_numeric_values() const;

    [[nodiscard]] bool contains_cell_values() const;

    [[nodiscard]] int compute_average() const;

    void set_value_for_whole_matrix(std::any&& new_value);

public:
    MatrixValue() = default;

    [[nodiscard]] std::any GetValue() const override;

    void SetValue(std::any&& new_value) override;

    bool operator == (const ValueInterface& other) const override;

    bool operator < (const ValueInterface& other) const override;

    bool operator > (const ValueInterface& other) const override;

    std::unique_ptr<ValueInterface> operator + (const ValueInterface& other) const override;

    std::unique_ptr<ValueInterface> operator - (const ValueInterface& other) const override;

    std::unique_ptr<ValueInterface> operator * (const ValueInterface& other) const override;

    std::unique_ptr<ValueInterface> operator / (const ValueInterface& other) const override;

    std::unique_ptr<ValueInterface> operator % (const ValueInterface& other) const override;

    std::unique_ptr<ValueInterface> operator ^ (const ValueInterface& other) const override;

    const ValueInterface& operator () (size_t i, size_t j) const override;

    ValueInterface& operator () (size_t i, size_t j) override;
};

#endif //INTERPRETER_MATRIX_VALUE_H