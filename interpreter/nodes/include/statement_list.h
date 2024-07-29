#ifndef INTERPRETER_STATEMENT_LIST_H
#define INTERPRETER_STATEMENT_LIST_H
#include "node_interface.h"
#include <vector>
#include "printable_interface.h"

class StatementListNode: public INode, public IPrintable{
public:
    StatementListNode();

    void AddStatement(std::unique_ptr<INode>&& statement);

    void Accept(NodeVisitor& visitor) const override;

    [[nodiscard]] std::size_t NumOfStatements() const noexcept;

    const std::unique_ptr<INode>& operator [] (size_t index) const;

    void PrintOut(std::ostream& stream) const override;

private:
    std::vector<std::unique_ptr<INode>> statements_;
};

#endif //INTERPRETER_STATEMENT_LIST_H
