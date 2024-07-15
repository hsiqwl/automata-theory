#include "interpreter.h"
#include "node_traits.h"

void Interpreter::Visit(const NumericLiteralNode &node) {
    Return(node.GetValue());
}

void Interpreter::Visit(const UnaryOpNode &node) {
    switch (node.GetOpKind()) {
        case UnaryOpKind::Minus: {
            Return(-GetValue(node.GetOperand()));
            break;
        }
        case UnaryOpKind::Plus: {
            Return(GetValue(node.GetOperand()));
            break;
        }
    }
}

void Interpreter::Visit(const BinaryOpNode &node) {
    switch (node.GetOpKind()) {
        case BinaryOpKind::Plus: {
            Return(GetValue(node.GetLeft()) + GetValue(node.GetRight()));
            return;
        }
        case BinaryOpKind::Minus: {
            Return(GetValue(node.GetLeft()) - GetValue(node.GetRight()));
            break;
        }
        case BinaryOpKind::Star: {
            Return(GetValue(node.GetLeft()) * GetValue(node.GetRight()));
            break;
        }
        case BinaryOpKind::Slash: {
            Return(GetValue(node.GetLeft()) / GetValue(node.GetRight()));
            break;
        }
    }
}

void Interpreter::Visit(const IdentifierNode &node) {
    // HERE SHOULD BE SOME CODE
}