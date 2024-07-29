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
    TypeHolder() = default;

    TypeHolder(TypeToken simple_type_token);

    void MakeMatrixWrap();
};


class TypeHolderWrapper{
private:
    std::deque<TypeToken> type_;

    bool IsNumericType() const noexcept;

    bool IsCellType() const noexcept;

public:
    TypeHolderWrapper(const TypeHolder& type_holder);

    TypeHolderWrapper() = default;

    bool IsSameAs(const TypeHolderWrapper& other) const noexcept;

    bool IsConvertibleTo(const TypeHolderWrapper& other) const noexcept;

    bool IsSimpleType() const noexcept;

    TypeToken GetSimpleType() const;

    bool IsNoneType() const noexcept;
};
#endif //INTERPRETER_TYPE_HOLDER_H
