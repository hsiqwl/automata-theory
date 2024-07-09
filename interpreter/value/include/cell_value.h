#ifndef INTERPRETER_CELL_VALUE_H
#define INTERPRETER_CELL_VALUE_H
#include "value_interface.h"
#include "cell.h"

class CellValue: public ValueInterface{
private:
    Cell value_;

public:
    CellValue() = default;

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


#endif //INTERPRETER_CELL_VALUE_H
