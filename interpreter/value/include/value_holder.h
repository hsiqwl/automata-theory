#ifndef INTERPRETER_VALUE_HOLDER_H
#define INTERPRETER_VALUE_HOLDER_H
#include <utility>

template <typename T>
requires(std::is_default_constructible_v<T>)
class ValueHolder {
protected:
    T value_;

public:
    ValueHolder(T value = T{}) : value_(value) {}
};

#endif //INTERPRETER_VALUE_HOLDER_H
