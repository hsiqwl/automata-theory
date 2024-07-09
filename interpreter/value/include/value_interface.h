#ifndef INTERPRETER_VALUE_HOLDER_H
#define INTERPRETER_VALUE_HOLDER_H
#include <memory>
#include <any>
#include <stdexcept>

class ValueInterface{
public:
    ValueInterface() = default;

    virtual ~ValueInterface() = default;

    virtual bool operator == (const ValueInterface& other) const = 0;

    virtual bool operator < (const ValueInterface& other) const = 0;

    virtual bool operator > (const ValueInterface& other) const = 0;

    virtual std::unique_ptr<ValueInterface> operator + (const ValueInterface& other) const = 0;

    virtual std::unique_ptr<ValueInterface> operator - (const ValueInterface& other) const = 0;

    virtual std::unique_ptr<ValueInterface> operator * (const ValueInterface& other) const = 0;

    virtual std::unique_ptr<ValueInterface> operator / (const ValueInterface& other) const = 0;

    virtual std::unique_ptr<ValueInterface> operator % (const ValueInterface& other) const = 0;

    virtual std::unique_ptr<ValueInterface> operator ^ (const ValueInterface& other) const = 0;

    virtual const ValueInterface& operator () (size_t i, size_t j) const = 0;

    virtual ValueInterface& operator () (size_t i, size_t j) = 0;

    virtual void SetValue(std::any&& new_value) = 0;

    [[nodiscard]] virtual std::any GetValue() const = 0;
};


#endif //INTERPRETER_VALUE_HOLDER_H
