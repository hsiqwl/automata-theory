#ifndef INTERPRETER_SEMANTIC_ERROR_H
#define INTERPRETER_SEMANTIC_ERROR_H
#include <stdexcept>

//POSSIBLE SEMANTIC ERRORS
// 1. USE OF UNDECLARED IDENTIFIER
// 2. REDECLARATION OF IDENTIFIER (WHEN IT HAS THE SAME TYPE)
// 3. CONFLICTING DECLARATION (WHEN SAME IDENTIFIER HAS MULTIPLE TYPES)
// 4. INVALID OPERAND TYPES
// 5. ASSIGNMENT OF CONST VARIABLE
// 6. NO KNOWN CONVERSION FROM TYPE_1 TO TYPE_2


class SemanticError: public std::exception {
protected:
    std::string msg_;

public:
    SemanticError(std::string_view err_msg);

    const char * what() const noexcept override;

    virtual ~SemanticError() = default;
};

class UseOfUndeclaredIdentifier: public SemanticError{
public:
    UseOfUndeclaredIdentifier();
};

class RedeclarationOfIdentifier: public SemanticError{
public:
    RedeclarationOfIdentifier();
};

class ConflictingDeclaration: public SemanticError {
public:
    ConflictingDeclaration();
};

class InvalidOperandTypes: public SemanticError{
public:
    InvalidOperandTypes();
};

class AssignmentOfConstVar: public SemanticError{
public:
    AssignmentOfConstVar();
};

class NoKnownConversion: public SemanticError{
public:
    NoKnownConversion();
};

class CallToUndeclaredFunction: public SemanticError{
public:
    CallToUndeclaredFunction();
};

class IncorrectNumberOfArguments: public SemanticError{
public:
    IncorrectNumberOfArguments();
};

class ArgumentsOfIncorrectType: public SemanticError{
public:
    ArgumentsOfIncorrectType();
};
#endif //INTERPRETER_SEMANTIC_ERROR_H
