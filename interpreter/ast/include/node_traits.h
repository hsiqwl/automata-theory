#ifndef INTERPRETER_NODE_TRAITS_H
#define INTERPRETER_NODE_TRAITS_H
#include "enums.h"
#include "binary_op.h"
#include "unary_op.h"
#include "numeric_literal.h"
#include "identifier_node.h"
#include <type_traits>

template<NodeKind Kind>
struct node_type_from_kind;

#define MAKE_NODE_TRAITS(t, kind) \
template <> struct node_type_from_kind<kind> \
{                                    \
    using type = t;                              \
}

MAKE_NODE_TRAITS(BinaryOpNode, NodeKind::BinaryOp);

MAKE_NODE_TRAITS(UnaryOpNode, NodeKind::UnaryOp);

MAKE_NODE_TRAITS(NumericLiteralNode, NodeKind::NumericLiteral);

MAKE_NODE_TRAITS(IdentifierNode, NodeKind::Identifier);


template<std::size_t Kind, typename = void>
struct kind_has_type : public std::false_type {};

template<std::size_t Kind>
struct kind_has_type<Kind, std::void_t<typename node_type_from_kind<static_cast<NodeKind>(Kind)>::type>>
: public std::true_type {};

template <std::size_t Kind, typename V = void>
struct min_valid_kind: public min_valid_kind<Kind + 1, V>{};

template<std::size_t Kind>
struct min_valid_kind<Kind, std::void_t<typename node_type_from_kind<static_cast<NodeKind>(Kind)>::type>>
: public std::integral_constant<std::size_t, Kind>{};


#endif //INTERPRETER_NODE_TRAITS_H
