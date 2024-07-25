#ifndef INTERPRETER_VALUE_TYPE_TRAITS_H
#define INTERPRETER_VALUE_TYPE_TRAITS_H
#include "type_token.h"
#include <type_traits>

class Cell;

//Conversion rules
template <TypeToken from, TypeToken to>
struct Convertible : public std::false_type {};

template<TypeToken type_token>
struct Convertible<type_token, type_token> : std::true_type {};

template<>
struct Convertible<TypeToken::Signed, TypeToken::Unsigned> : public std::true_type {};

template<>
struct Convertible<TypeToken::Unsigned, TypeToken::Signed> : public std::true_type {};

template<>
struct Convertible<TypeToken::Cell, TypeToken::Signed> : public std::true_type {};

template<>
struct Convertible<TypeToken::Cell, TypeToken::Unsigned> : public std::true_type {};

template<>
struct Convertible<TypeToken::Unsigned, TypeToken::Cell> : public std::true_type {};

template<>
struct Convertible<TypeToken::Signed, TypeToken::Cell> : public std::true_type {};

//Mapping types to type tokens
template<TypeToken type_token>
struct TypeFromToken;

template<>
struct TypeFromToken<TypeToken::Unsigned>{
    using type = unsigned ;
};

template<>
struct TypeFromToken<TypeToken::Signed>{
    using type = int;
};

template<>
struct TypeFromToken<TypeToken::Cell>{
    using type = Cell;
};

#endif //INTERPRETER_VALUE_TYPE_TRAITS_H
