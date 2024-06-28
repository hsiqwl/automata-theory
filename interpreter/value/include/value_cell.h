#ifndef INTERPRETER_VALUE_CELL_H
#define INTERPRETER_VALUE_CELL_H
#include "value_interface.h"
#include "cell.h"

class value_cell: public value_interface{
private:
    cell value;

public:
    value_cell() = default;

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


#endif //INTERPRETER_VALUE_CELL_H
