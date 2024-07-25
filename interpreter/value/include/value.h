#ifndef INTERPRETER_VALUE_H
#define INTERPRETER_VALUE_H
#include <any>
#include <concepts>
#include "value_interface.h"

class Value{
public:
    template <std::derived_from<IValue> ConcreteValue>
    Value(ConcreteValue&& value)
        : storage_(std::forward<ConcreteValue>(value)),
          getter_([](std::any& storage) -> IValue& {
              return std::any_cast<IValue&>(storage);}){}


    IValue* operator -> () {return &getter_(storage_);}

    IValue& operator * () {return getter_(storage_);}

private:
    std::any storage_;

    IValue& (*getter_)(std::any&);
};

#endif //INTERPRETER_VALUE_H
