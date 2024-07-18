#include "binary_op.h"
#include "node_visitor.h"


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
        case BinaryOpKind::Assign:
            label_ = "<-";
            return;
    }
}

BinaryOpNode::BinaryOpNode(BinaryOpKind op_kind, std::unique_ptr<INode>&& lhs, std::unique_ptr<INode>&& rhs)
    : INode(NodeKind::BinaryOp), op_kind_(op_kind), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
    SetLabel();
}

void BinaryOpNode::Accept(NodeVisitor &visitor) const {
   visitor.Visit(*this);
}

const std::unique_ptr<INode>& BinaryOpNode::GetLeft() const noexcept {
    return lhs_;
}

const std::unique_ptr<INode> &BinaryOpNode::GetRight() const noexcept {
    return rhs_;
}

BinaryOpKind BinaryOpNode::GetOpKind() const noexcept {
    return op_kind_;
}