#ifndef INTERPRETER_VALUE_GETTER_H
#define INTERPRETER_VALUE_GETTER_H
#include <type_traits>

template<typename VisitorImpl, typename NodePtr, typename ResultType>
requires (!std::is_void_v<ResultType>)
class ValueGetter{
public:
    static ResultType GetValue(const NodePtr& node){
        VisitorImpl visitor;
        node->Accept(visitor);
        return visitor.value_;
    }

    void Return(ResultType value){
        value_ = value;
    }

private:
    ResultType value_;
};
#endif //INTERPRETER_VALUE_GETTER_H
