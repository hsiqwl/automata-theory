#ifndef INTERPRETER_NODE_TRAITS_H
#define INTERPRETER_NODE_TRAITS_H
#include "enums.h"
#include "binary_op.h"
#include "unary_op.h"
#include "signed_literal.h"
#include "unsigned_literal.h"
#include "var_ref.h"
#include "var_decl.h"
#include "assign.h"
#include "initialization.h"
#include "statement_list.h"
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

MAKE_NODE_TRAITS(VarReferenceNode, NodeKind::VarRef);

MAKE_NODE_TRAITS(VarDeclNode, NodeKind::VarDecl);

MAKE_NODE_TRAITS(AssignNode, NodeKind::Assign);

MAKE_NODE_TRAITS(StatementListNode, NodeKind::StatementList);

MAKE_NODE_TRAITS(SignedLiteralNode, NodeKind::SignedLiteral);

MAKE_NODE_TRAITS(UnsignedLiteralNode, NodeKind::UnsignedLiteral);

MAKE_NODE_TRAITS(InitializationNode, NodeKind::Initialization);


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
