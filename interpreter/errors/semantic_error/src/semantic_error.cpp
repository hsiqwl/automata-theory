#include "semantic_error.h"

SemanticError::SemanticError(std::string_view err_msg): std::exception(), msg_(err_msg) {}

const char *SemanticError::what() const noexcept {
    return msg_.c_str();
}

UseOfUndeclaredIdentifier::UseOfUndeclaredIdentifier(): SemanticError("Use of undeclared identifier") {}

RedeclarationOfIdentifier::RedeclarationOfIdentifier(): SemanticError("Redeclaration of identifier") {}

ConflictingDeclaration::ConflictingDeclaration(): SemanticError("Conflicting declaration") {}

InvalidOperandTypes::InvalidOperandTypes(): SemanticError("Invalid operand types") {}

AssignmentOfConstVar::AssignmentOfConstVar(): SemanticError("Assignment of const variable") {}

NoKnownConversion::NoKnownConversion(): SemanticError("No known conversion") {}

CallToUndeclaredFunction::CallToUndeclaredFunction(): SemanticError("Call to undeclared function") {}

IncorrectNumberOfArguments::IncorrectNumberOfArguments(): SemanticError("Incorrect number of arguments") {}

ArgumentsOfIncorrectType::ArgumentsOfIncorrectType(): SemanticError("Arguments of incorrect type") {}