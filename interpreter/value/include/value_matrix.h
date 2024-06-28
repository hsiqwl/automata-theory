#ifndef INTERPRETER_VALUE_MATRIX_H
#define INTERPRETER_VALUE_MATRIX_H
#include "value_interface.h"
#include "value_signed.h"
#include "value_unsigned.h"
#include "value_cell.h"
#include <vector>

class value_matrix: public value_interface{
public:
    typedef std::vector<std::vector<std::shared_ptr<value_interface>>> matrix;

private:
    matrix value;

    [[nodiscard]] bool contains_numeric_values() const;

    [[nodiscard]] bool contains_cell_values() const;

    [[nodiscard]] int compute_average() const;

    void set_value_for_whole_matrix(std::any&& new_value);

public:
    value_matrix() = default;

    [[nodiscard]] std::any get_value() const override;

    void set_value(std::any&& new_value) override;

    bool operator == (const value_interface& other) const override;

    bool operator < (const value_interface& other) const override;

    bool operator > (const value_interface& other) const override;

    std::unique_ptr<value_interface> operator + (const value_interface& other) const override;

    std::unique_ptr<value_interface> operator - (const value_interface& other) const override;

    std::unique_ptr<value_interface> operator * (const value_interface& other) const override;

    std::unique_ptr<value_interface> operator / (const value_interface& other) const override;

    std::unique_ptr<value_interface> operator % (const value_interface& other) const override;

    std::unique_ptr<value_interface> operator ^ (const value_interface& other) const override;

    const value_interface& operator () (size_t i, size_t j) const override;

    value_interface& operator () (size_t i, size_t j) override;
};

#endif //INTERPRETER_VALUE_MATRIX_H
