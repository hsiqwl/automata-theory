#ifndef INTERPRETER_VALUE_GETTER_H
#define INTERPRETER_VALUE_GETTER_H
#include <type_traits>
#include "sharable_object_holder.h"

template<typename VisitorImpl, typename NodePtr, typename ResultType>
requires (!std::is_void_v<ResultType>)
class ValueGetter{
public:
    static ResultType GetValue(const NodePtr& node){
        VisitorImpl visitor;
        node->Accept(visitor);
        return visitor.value_;
    }

    void Return(ResultType&& value){
        value_ = std::forward<ResultType>(value);
    }

private:
    ResultType value_;
};

template<typename VisitorImpl, typename NodePtr, typename ResultType>
requires (!std::is_void_v<ResultType>)
class ValueGetterWithSharableObjectHolder{
public:
    template<typename SharableObject>
    static ResultType GetValue(const NodePtr& node, SharableObject* ptr){
        VisitorImpl visitor(ptr);
        node->Accept(visitor);
        return visitor.value_;
    }

    void Return(ResultType value){
        value_ = std::move(value);
    }

private:
    ResultType value_;
};

#endif //INTERPRETER_VALUE_GETTER_H
