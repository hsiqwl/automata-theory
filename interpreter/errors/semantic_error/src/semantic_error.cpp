#include "semantic_error.h"

const char *SemanticError::what() const noexcept {
    return msg_.c_str();
}

UseOfUndeclaredIdentifier::UseOfUndeclaredIdentifier(const yy::location &loc, std::string_view id) {
    msg_
    = (boost::format("In file: %1%, at %2%:%3% - %4%:%5%: use of undeclared identifier: %6%")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column % id).str();
}

InvalidIdentifierUsage::InvalidIdentifierUsage(const yy::location &loc, std::string_view id) {
    msg_
    = (boost::format("In file: %1%, at %2%:%3% - %4%:%5%: invalid usage of identifier: %6%")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column % id).str();
}

RedeclarationOfIdentifier::RedeclarationOfIdentifier(const yy::location &loc, std::string_view id) {
    msg_
    = (boost::format("In file: %1%, at %2%:%3% - %4%:%5%: redeclaration of identifier: %6%."
                     " Identifier with same type was declared before")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column % id).str();
}

ConflictingDeclaration::ConflictingDeclaration(const yy::location &loc, std::string_view id) {
    msg_
    = (boost::format("In file: %1%, at %2%:%3% - %4%:%5%: conflicting declaration of identifier: %6%."
                     " Same identifier with different type was declared before")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column % id).str();
}

InvalidOperandTypes::InvalidOperandTypes(const yy::location &loc) {
    msg_
    = (boost::format("In file: %1%, at %2%:%3% - %4%:%5%: invalid operand types")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column).str();
}

AssignmentOfConstVar::AssignmentOfConstVar(const yy::location &loc) {
    msg_
    = (boost::format("In file: %1%, at %2%:%3% - %4%:%5%: Cannot assign read-only variable")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column).str();
}

NoKnownConversion::NoKnownConversion(const yy::location &loc, const TypeHolderWrapper &from,
                                     const TypeHolderWrapper &to) {
    msg_
    = (boost::format("In file: %1, at %2%:%3% - %4%:%5%: Cannot convert from type '%6%' to type '%7%'")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column %
            from.GetStringRepresentation() % to.GetStringRepresentation()).str();
}

CallToUndeclaredFunction::CallToUndeclaredFunction(const yy::location &loc, std::string_view id) {
    msg_
    = (boost::format("In file: %1, at %2%:%3% - %4%:%5%: call to undeclared function '%6%'")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column
            % id).str();
}

IncorrectNumberOfArguments::IncorrectNumberOfArguments(const yy::location &loc, std::string_view id, size_t expected,
                                                       size_t actual) {
    msg_
    = (boost::format("In file: %1, at %2%:%3% - %4%:%5%: when calling function '%6%' expected %7% args, but passed only %8%")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column
            % id % expected % actual).str();
}

ArgumentsOfIncorrectType::ArgumentsOfIncorrectType(const yy::location &loc, std::string_view id,
                                                   const TypeHolderWrapper &expected, const TypeHolderWrapper &actual) {
    msg_
    = (boost::format("In file: %1, at %2%:%3% - %4%:%5%: when calling function '%6%' expected arg of '%7%' type, but passed of type '%8%'")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column
            % id % expected.GetStringRepresentation() % actual.GetStringRepresentation()).str();
}

UninitializedConstVariable::UninitializedConstVariable(const yy::location &loc, std::string_view id) {
    msg_
    = (boost::format("In file: %1, at %2%:%3% - %4%:%5%: const variable %6% must be initialized when declared")
            % *loc.begin.filename % loc.begin.line % loc.begin.column % loc.end.line % loc.end.column
            % id).str();
}