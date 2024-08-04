#ifndef INTERPRETER_VAR_DECL_H
#define INTERPRETER_VAR_DECL_H
#include "node_interface.h"
#include "type_holder.h"
#include "printable_interface.h"

class VarDeclNode: public INode, public IPrintable{
public:
    VarDeclNode(std::string_view name, const TypeHolder &type, const location_t &loc, bool is_const = false);

    [[nodiscard]] const std::string& GetName() const noexcept;

    [[nodiscard]] const TypeHolderWrapper & GetType() const  noexcept;

    [[nodiscard]] bool IsConst() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream& stream) const override;

private:
    std::string name_;

    TypeHolderWrapper type_;

    bool const_;
};

#endif //INTERPRETER_VAR_DECL_H
