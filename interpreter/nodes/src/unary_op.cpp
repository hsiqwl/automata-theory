#include "unary_op.h"
#include "node_visitor.h"

char UnaryOpNode::GetLabel() const{
    switch (op_kind_) {
        case UnaryOpKind::Plus: {
            return '+';
        }
        case UnaryOpKind::Minus:{
            return '-';
        }
    }
}

UnaryOpNode::UnaryOpNode(UnaryOpKind op_kind, std::unique_ptr<INode>&& operand)
    : INode(NodeKind::UnaryOp), operand_(std::move(operand)), op_kind_(op_kind) {}

void UnaryOpNode::Accept(NodeVisitor &visitor) const{
    visitor.Visit(*this);
}

UnaryOpKind UnaryOpNode::GetOpKind() const noexcept {
    return op_kind_;
}

const std::unique_ptr<INode> &UnaryOpNode::GetOperand() const noexcept {
    return operand_;
}

void UnaryOpNode::PrintOut(std::ostream &stream) const {
    auto fmt_string = std::format("UnaryOpNode : '{}'", GetLabel());
    stream << fmt_string << '\n';
}