#include "type_holder.h"

TypeHolder::TypeHolder(TypeToken simple_type_token) {
    if(simple_type_token != TypeToken::Matrix)
        type_.push_front(simple_type_token);
    else
        throw std::logic_error("cannot start type with non built-in type");
}

void TypeHolder::MakeMatrixWrap() {
    type_.push_front(TypeToken::Matrix);
}

TypeHolderWrapper::TypeHolderWrapper(const TypeHolder &type_holder) {
    type_ = type_holder.type_;
}

bool TypeHolderWrapper::IsSameAs(const TypeHolderWrapper &other) const noexcept {
    return type_ == other.type_;
}

bool TypeHolderWrapper::IsSimpleType() const noexcept {
    return type_.size() == 1;
}

TypeToken TypeHolderWrapper::GetSimpleType() const {
    if (IsSimpleType())
        return type_.back();
    else
        throw std::logic_error("Type is not simple, but compound");
}