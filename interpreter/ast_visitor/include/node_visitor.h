#ifndef INTERPRETER_NODE_VISITOR_H
#define INTERPRETER_NODE_VISITOR_H

class BinaryOpNode;
class UnaryOpNode;
class IdentifierNode;
class NumericLiteralNode;

class NodeVisitor{
public:
    virtual void Visit(BinaryOpNode& node) = 0;

    virtual void Visit(UnaryOpNode& node) = 0;

    virtual void Visit(IdentifierNode& node) = 0;

    virtual void Visit(NumericLiteralNode& node) = 0;

    virtual ~NodeVisitor() = default;
};

#endif //INTERPRETER_NODE_VISITOR_H
