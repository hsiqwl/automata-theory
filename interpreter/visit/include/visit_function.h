#ifndef INTERPRETER_VISIT_FUNCTION_H
#define INTERPRETER_VISIT_FUNCTION_H
#include "node_traits.h"

constexpr std::size_t MAX_TOKEN_NAMES_ID_ = static_cast<std::size_t>(NodeKind::MAX_TOKEN_NAMES_ID);

template <std::size_t Kind>
Node* UnsafeTo(Node* node) {
    return static_cast<node_type_from_kind<static_cast<NodeKind>(Kind)>::type *>(node);
}

template <class Fun, class C = std::bool_constant<true>, std::size_t N = MAX_TOKEN_NAMES_ID_,
        class ...Types>
struct invoke_result: public invoke_result<Fun, C, N - 1, Types...>{};

template <class Fun, class C, class ...Types>
struct invoke_result<Fun, C, min_valid_kind<0>::value, Types...>{
    using type = std::common_type_t<Types...>;
};

template <class Fun, std::size_t N, class ...Types>
struct invoke_result<Fun,
        std::bool_constant<
                std::conjunction_v<
                        kind_has_type<N>,
                        typename std::is_invocable<
                        Fun,
                        typename node_type_from_kind<static_cast<NodeKind>(N)>::type&
                        >
                >
        >,
        N, Types...>
: public invoke_result<Fun, std::bool_constant<true>, N - 1,
    std::invoke_result_t<Fun, typename node_type_from_kind<static_cast<NodeKind>(N)>::type&>, Types...>{};


template<class ReturnType, class Fun, class Node, std::size_t Kind,
        typename = std::bool_constant<true>>
struct function_value{
    static constexpr ReturnType(*value)(Fun&&, Node&) = nullptr;
};


template <class ReturnType, class Fun, class Node, std::size_t Kind>
struct function_value<ReturnType, Fun, Node, Kind,
        std::bool_constant<kind_has_type<Kind>::value>>{
    static constexpr ReturnType(*value)(Fun&&, Node&) =
            +[](Fun&& fun, Node& node) -> ReturnType {
                return fun(*UnsafeTo<Kind>(&node));
    };
};

template<std::size_t MinKind, class Fun,
        class Node, std::size_t Id, std::size_t ...Idx>
auto Visit(Fun&& fun, Node& node, std::index_sequence<Id, Idx...>) {
    using ReturnType = invoke_result<Fun>::value;

    static constexpr ReturnType (*vtable[])(Fun &&, Node &) = {
            (function_value<ReturnType, Fun, Node, MinKind + Id>::value),
            (function_value<ReturnType, Fun, Node, MinKind + Idx>::value)...
    };
    return vtable[node.GetKind() - MinKind](std::forward<Fun>(fun), node);
}

template<class Fun, class Node>
auto Visit(Fun&& fun, Node& node){
    static constexpr auto min_kind = min_valid_kind<0>::value;
    return Visit<min_kind>(std::forward<Fun>(fun),
            node,
            std::make_index_sequence<MAX_TOKEN_NAMES_ID_ - min_kind>{});
}



#endif //INTERPRETER_VISIT_FUNCTION_H
