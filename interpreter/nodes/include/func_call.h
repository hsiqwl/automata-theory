#ifndef INTERPRETER_FUNC_CALL_H
#define INTERPRETER_FUNC_CALL_H
#include "node_interface.h"
#include "printable_interface.h"
#include <vector>

class FuncCall: public INode, public IPrintable {
public:
    FuncCall(std::string_view func_name, std::vector<std::unique_ptr<INode>>&& args);

    const std::string& GetFuncName() const noexcept;

    const std::vector<std::unique_ptr<INode>>& GetArgs() const noexcept;

    void Accept(NodeVisitor& visitor) const override;

    void PrintOut(std::ostream & stream) const override;

private:
    std::string func_name_;

    std::vector<std::unique_ptr<INode>> args_;

};

#endif //INTERPRETER_FUNC_CALL_H
