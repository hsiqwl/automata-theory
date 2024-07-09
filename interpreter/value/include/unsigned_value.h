#ifndef INTERPRETER_UNSIGNED_VALUE_H
#define INTERPRETER_UNSIGNED_VALUE_H
#include "value_interface.h"


class UnsignedValue: public ValueInterface{
private:
    unsigned int value_ = 0;

public:
    UnsignedValue() = default;

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

#endif //INTERPRETER_UNSIGNED_VALUE_H
