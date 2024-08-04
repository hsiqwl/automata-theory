#ifndef INTERPRETER_VAR_REF_H
#define INTERPRETER_VAR_REF_H
#include "node_interface.h"
#include "printable_interface.h"

class VarReferenceNode: public INode, public IPrintable{
public:
    VarReferenceNode(std::string_view name, const location_t &loc);

    [[nodiscard]] const std::string& GetVarName() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream& stream) const override;

private:
    std::string var_name_;

};

#endif //INTERPRETER_VAR_REF_H
