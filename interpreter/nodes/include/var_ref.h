#ifndef INTERPRETER_VAR_REF_H
#define INTERPRETER_VAR_REF_H
#include "node_interface.h"

class VarReferenceNode: public INode{
public:
    VarReferenceNode(std::string_view name);

    [[nodiscard]] const std::string& GetVarName() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

private:
    std::string var_name_;

};

#endif //INTERPRETER_VAR_REF_H
