#ifndef INTERPRETER_TYPE_HOLDER_H
#define INTERPRETER_TYPE_HOLDER_H
#include "type_token.h"
#include <deque>
#include <variant>
#include <stdexcept>

class TypeHolderWrapper;

class TypeHolder{
private:
    std::deque<TypeToken> type_;

    friend class TypeHolderWrapper;

public:
    TypeHolder(TypeToken simple_type_token);

    void MakeMatrixWrap();
};


class TypeHolderWrapper{
private:
    std::deque<TypeToken> type_;

public:
    TypeHolderWrapper(const TypeHolder& type_holder);

    bool IsSameAs(const TypeHolderWrapper& other) const noexcept;

    bool IsSimpleType() const noexcept;

    TypeToken GetSimpleType() const;
};
#endif //INTERPRETER_TYPE_HOLDER_H
