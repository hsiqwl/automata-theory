#ifndef INTERPRETER_VAR_DECL_H
#define INTERPRETER_VAR_DECL_H
#include "node_interface.h"

class VarDeclNode: public INode{
public:
    VarDeclNode(std::string_view name, std::string_view type, bool is_const = false);

    [[nodiscard]] const std::string& GetName() const noexcept;

    [[nodiscard]] const std::string& GetType() const noexcept;

    [[nodiscard]] bool IsConst() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

private:
    std::string name_;

    std::string type_;

    bool const_;
};

#endif //INTERPRETER_VAR_DECL_H
