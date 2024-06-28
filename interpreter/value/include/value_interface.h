#ifndef INTERPRETER_VALUE_HOLDER_H
#define INTERPRETER_VALUE_HOLDER_H
#include <memory>
#include <any>
#include <stdexcept>

class value_interface{
public:
    value_interface() = default;

    virtual ~value_interface() = default;

    virtual bool operator == (const value_interface& other) const = 0;

    virtual bool operator < (const value_interface& other) const = 0;

    virtual bool operator > (const value_interface& other) const = 0;

    virtual std::unique_ptr<value_interface> operator + (const value_interface& other) const = 0;

    virtual std::unique_ptr<value_interface> operator - (const value_interface& other) const = 0;

    virtual std::unique_ptr<value_interface> operator * (const value_interface& other) const = 0;

    virtual std::unique_ptr<value_interface> operator / (const value_interface& other) const = 0;

    virtual std::unique_ptr<value_interface> operator % (const value_interface& other) const = 0;

    virtual std::unique_ptr<value_interface> operator ^ (const value_interface& other) const = 0;

    virtual const value_interface& operator () (size_t i, size_t j) const = 0;

    virtual value_interface& operator () (size_t i, size_t j) = 0;

    virtual void set_value(std::any&& new_value) = 0;

    [[nodiscard]] virtual std::any get_value() const = 0;
};


#endif //INTERPRETER_VALUE_HOLDER_H
