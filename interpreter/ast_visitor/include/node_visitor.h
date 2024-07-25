#ifndef INTERPRETER_NODE_VISITOR_H
#define INTERPRETER_NODE_VISITOR_H

class BinaryOpNode;
class UnaryOpNode;
class SignedLiteralNode;
class UnsignedLiteralNode;
class VarDeclNode;
class VarReferenceNode;
class AssignNode;
class InitializationNode;
class StatementListNode;

class NodeVisitor {
public:
    virtual void Visit(const BinaryOpNode &node) = 0;

    virtual void Visit(const UnaryOpNode &node) = 0;

    virtual void Visit(const SignedLiteralNode &node) = 0;

    virtual void Visit(const UnsignedLiteralNode& node) = 0;

    virtual void Visit(const VarDeclNode &node) = 0;

    virtual void Visit(const VarReferenceNode &node) = 0;

    virtual void Visit(const AssignNode &node) = 0;

    virtual void Visit(const InitializationNode& node) = 0;

    virtual void Visit(const StatementListNode &node) = 0;


    virtual ~NodeVisitor() = default;
};

#endif //INTERPRETER_NODE_VISITOR_H
