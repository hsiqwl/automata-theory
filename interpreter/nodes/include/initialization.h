#ifndef INTERPRETER_INITIALIZATION_H
#define INTERPRETER_INITIALIZATION_H
#include "node_interface.h"
#include <any>

class InitializationNode: public INode{
    InitializationNode(std::string_view var_to_init, std::unique_ptr<INode>&& init_expr = nullptr);

    const std::unique_ptr<INode>& GetInitExpr() const noexcept;

    const std::string& GetVarName() const noexcept;

    void Accept(NodeVisitor& visitor) const override;
private:
    std::string var_to_init_;

    std::unique_ptr<INode> init_expr_;
};

#endif //INTERPRETER_INITIALIZATION_H
