#include "semantic_analyzer_caller.h"

SemanticErrorContext SemanticAnalyzerCaller::CallAnalyzer(const Ast &tree) {
    return SemanticAnalyzer::GetValue(tree.GetRoot().get(), &symbol_table_);
}