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

    bool const_qualified_ = false;

    friend class TypeHolderWrapper;

public:
    TypeHolder() = default;

    TypeHolder(TypeToken simple_type_token);

    void MakeMatrixWrap();

    void MakeConst() noexcept;
};


class TypeHolderWrapper{
private:
    std::deque<TypeToken> type_;

    bool const_qualified_;

    bool IsNumericType() const noexcept;

    bool IsCellType() const noexcept;

    static std::string GetStringForTypeToken(TypeToken token) noexcept;

public:
    TypeHolderWrapper(const TypeHolder& type_holder);

    TypeHolderWrapper() = default;

    bool IsSameAs(const TypeHolderWrapper& other) const noexcept;

    bool IsConvertibleTo(const TypeHolderWrapper& other) const noexcept;

    bool IsSimpleType() const noexcept;

    TypeToken GetSimpleType() const;

    bool IsNoneType() const noexcept;

    bool IsConst() const noexcept;

    std::string GetStringRepresentation() const noexcept;
};
#endif //INTERPRETER_TYPE_HOLDER_H
