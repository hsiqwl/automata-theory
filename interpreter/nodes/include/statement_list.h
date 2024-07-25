#ifndef INTERPRETER_STATEMENT_LIST_H
#define INTERPRETER_STATEMENT_LIST_H
#include "node_interface.h"
#include <vector>

class StatementListNode: public INode{
public:
    StatementListNode();

    void AddStatement(std::unique_ptr<INode>&& statement);

    void Accept(NodeVisitor& visitor) const override;

    [[nodiscard]] std::size_t NumOfStatements() const noexcept;

    const std::unique_ptr<INode>& operator [] (int index) const;

private:
    std::vector<std::unique_ptr<INode>> statements_;
};

#endif //INTERPRETER_STATEMENT_LIST_H
