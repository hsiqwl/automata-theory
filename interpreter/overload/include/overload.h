#ifndef INTERPRETER_OVERLOAD_H
#define INTERPRETER_OVERLOAD_H

template <typename... Types>
struct Overload: Types ... {
    using Types::operator() ... ;
};

template<typename... Types>
Overload(Types...) -> Overload<Types...>;

#endif //INTERPRETER_OVERLOAD_H
