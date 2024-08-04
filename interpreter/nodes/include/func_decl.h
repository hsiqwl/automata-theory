#ifndef INTERPRETER_FUNC_DECL_H
#define INTERPRETER_FUNC_DECL_H
#include "node_interface.h"
#include "printable_interface.h"
#include "var_decl.h"
#include "statement_list.h"

class FuncDeclNode: public INode, public IPrintable {
public:
    FuncDeclNode(std::string_view func_name, std::unique_ptr<StatementListNode> &&body,
                 std::vector<std::unique_ptr<VarDeclNode>> &&params, const location_t &loc);

    const std::string& GetFuncName() const noexcept;

    const std::unique_ptr<StatementListNode>& GetFuncBody() const noexcept;

    const std::vector<std::unique_ptr<VarDeclNode>>& GetFuncParams() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream & stream) const override;

private:
    std::string func_name_;

    std::vector<std::unique_ptr<VarDeclNode>> params_;

    std::unique_ptr<StatementListNode> body_;
};

#endif //INTERPRETER_FUNC_DECL_H
