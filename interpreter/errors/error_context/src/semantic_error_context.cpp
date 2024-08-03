#include "semantic_error_context.h"

SemanticErrorContext::SemanticErrorContext(std::shared_ptr<SemanticError> &&error) {
    errors_.emplace_back(std::move(error));
}

void SemanticErrorContext::Add(std::shared_ptr<SemanticError> &&error) {
    errors_.emplace_back(std::move(error));
}

void SemanticErrorContext::Add(SemanticErrorContext &&context) {
    std::move(context.errors_.begin(), context.errors_.end(), std::back_inserter(errors_));
}

bool SemanticErrorContext::IsEmpty() const noexcept {
    return errors_.empty();
}

void SemanticErrorContext::PrintOut(std::ostream &stream) const {
    if (IsEmpty())
        stream << "Semantic error context is empty, there are no semantic errors in your program\n";
    else {
        for (const auto &error: errors_)
            stream << error->what() << "\n";
    }
}

std::ostream& operator << (std::ostream& stream, const SemanticErrorContext& context) {
    context.PrintOut(stream);
    return stream;
}
