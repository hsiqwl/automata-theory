#include "binary_op.h"
#include "node_visitor.h"

char BinaryOpNode::GetLabel() const{
    switch (op_kind_) {
        case BinaryOpKind::Plus:
            return '+';
        case BinaryOpKind::Minus:
            return '-';
        case BinaryOpKind::Star:
            return '*';
        case BinaryOpKind::Slash:
            return '/';
        case BinaryOpKind::Percent:
            return '%';
        case BinaryOpKind::Less:
            return '<';
        case BinaryOpKind::Greater:
            return '>';
        case BinaryOpKind::Equal:
            return '=';
    }
}

BinaryOpNode::BinaryOpNode(BinaryOpKind op_kind, std::unique_ptr<INode> &&lhs, std::unique_ptr<INode> &&rhs,
                           const location_t &loc)
    : INode(NodeKind::BinaryOp, loc), op_kind_(op_kind), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {
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

void BinaryOpNode::PrintOut(std::ostream &stream) const {
    auto fmt_string = std::format("BinaryOpNode: '{}'", GetLabel());
    stream << fmt_string << '\n';
}