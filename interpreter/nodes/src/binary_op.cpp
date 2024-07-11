#include "binary_op.h"

void BinaryOpNode::SetLabel() {
    switch (op_kind_) {
        case BinaryOpKind::Plus:
            label_ = "+";
            return;
        case BinaryOpKind::Minus:
            label_ = "-";
            return;
        case BinaryOpKind::Star:
            label_ = "*";
            return;
        case BinaryOpKind::Slash:
            label_ = "/";
            return;
        case BinaryOpKind::Percent:
            label_ = "%";
            return;
        case BinaryOpKind::Less:
            label_ = "<";
            return;
        case BinaryOpKind::Greater:
            label_ = ">";
            return;
        case BinaryOpKind::Equal:
            label_ = "=";
            return;
    }
}

BinaryOpNode::BinaryOpNode(BinaryOpKind op_kind, INode* lhs, INode* rhs)
    : INode(NodeKind::BinaryOp), op_kind_(op_kind), lhs_(lhs), rhs_(rhs) {
    SetLabel();
}

void BinaryOpNode::PrintOut(std::ostream &stream) const {
    stream << "BinaryOp : '" << label_ << "'\n";
}