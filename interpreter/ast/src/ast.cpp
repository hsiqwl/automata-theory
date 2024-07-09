#include "ast.h"

ast::ast(std::shared_ptr<node> &&root) :root(std::move(root)) {}