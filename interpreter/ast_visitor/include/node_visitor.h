#ifndef INTERPRETER_NODE_VISITOR_H
#define INTERPRETER_NODE_VISITOR_H

class BinaryOpNode;
class UnaryOpNode;
class NumericLiteralNode;
class VarDeclNode;
class VarReferenceNode;

class NodeVisitor{
public:
    virtual void Visit(const BinaryOpNode& node) = 0;

    virtual void Visit(const UnaryOpNode& node) = 0;

    virtual void Visit(const NumericLiteralNode& node) = 0;

    virtual void Visit(const VarDeclNode& node) = 0;

    virtual void Visit(const VarReferenceNode& node) = 0;

    virtual ~NodeVisitor() = default;
};

#endif //INTERPRETER_NODE_VISITOR_H
