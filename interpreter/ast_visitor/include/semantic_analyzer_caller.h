#ifndef INTERPRETER_SEMANTIC_ANALYZER_CALLER_H
#define INTERPRETER_SEMANTIC_ANALYZER_CALLER_H
#include "semantic_analyzer.h"
#include "ast.h"

class SemanticAnalyzerCaller {
public:
    SemanticErrorContext CallAnalyzer(const Ast &tree);

private:
    SymbolTableManager symbol_table_;
};

#endif //INTERPRETER_SEMANTIC_ANALYZER_CALLER_H
