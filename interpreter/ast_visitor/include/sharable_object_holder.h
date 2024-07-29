#ifndef INTERPRETER_SHARABLE_OBJECT_HOLDER_H
#define INTERPRETER_SHARABLE_OBJECT_HOLDER_H

template<typename SharableObj>
class SharableObjectHolder{
protected:
    SharableObj* object_ptr_;

public:
    SharableObjectHolder(SharableObj* ptr) {object_ptr_ = ptr;}

    virtual ~SharableObjectHolder() = default;
};

#endif //INTERPRETER_SHARABLE_OBJECT_HOLDER_H
