#ifndef INTERPRETER_ENUMS_H
#define INTERPRETER_ENUMS_H

enum class NodeKind{
    BinaryOp,
    UnaryOp,
    SignedLiteral,
    UnsignedLiteral,
    VarDecl,
    VarRef,
    Assign,
    Initialization,
    StatementList,
    IfNode,
    WhileNode,
    FuncDecl,
    FuncCall,
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
