#ifndef INTERPRETER_ENUMS_H
#define INTERPRETER_ENUMS_H

enum class NodeKind{
    BinaryOp,
    UnaryOp,
    Identifier,
    NumericLiteral,
    MAX_TOKEN_NAMES_ID
};

enum class BinaryOpKind{
    Plus,
    Minus,
    Star,
    Slash,
    Less,
    Greater,
    Equal,
    Percent
};

enum class UnaryOpKind{
    Plus,
    Minus
};

#endif //INTERPRETER_ENUMS_H
