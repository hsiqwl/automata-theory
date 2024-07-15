#ifndef INTERPRETER_VALUE_GETTER_H
#define INTERPRETER_VALUE_GETTER_H

template<typename VisitorImpl, typename NodePtr, typename ResultType>
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
