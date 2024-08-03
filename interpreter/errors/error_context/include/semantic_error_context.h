#ifndef INTERPRETER_SEMANTIC_ERROR_CONTEXT_H
#define INTERPRETER_SEMANTIC_ERROR_CONTEXT_H
#include "semantic_error.h"
#include <vector>
#include <memory>
#include <algorithm>
#include "printable_interface.h"

class SemanticErrorContext: public IPrintable{
private:
    std::vector<std::shared_ptr<SemanticError>> errors_;

public:
    SemanticErrorContext() = default;

    SemanticErrorContext(std::shared_ptr<SemanticError> &&error);

    void Add(SemanticErrorContext&& context);

    void Add(std::shared_ptr<SemanticError> &&error);

    bool IsEmpty() const noexcept;

    void PrintOut(std::ostream &stream) const override;
};

std::ostream& operator << (std::ostream& stream, const SemanticErrorContext& context);

#endif //INTERPRETER_SEMANTIC_ERROR_CONTEXT_H
