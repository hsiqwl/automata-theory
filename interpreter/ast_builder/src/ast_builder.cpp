#include "ast_builder.h"

void ast_builder::build_operation(std::unique_ptr<node> &&operation_node) {
    tree.root = std::move(operation_node);
}