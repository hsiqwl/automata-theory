#include "unary_op.h"
#include "node_visitor.h"

void UnaryOpNode::SetLabel() {
    switch (op_kind_) {
        case UnaryOpKind::Plus: {
            label_ = "+";
        }
        case UnaryOpKind::Minus:{
            label_ = "-";
        }
    }
}

void UnaryOpNode::PrintOut(std::ostream &stream) const {
    stream << "UnaryOpNode : '" << label_ << "'\n";
}

UnaryOpNode::UnaryOpNode(UnaryOpKind op_kind, std::unique_ptr<INode>&& operand)
    : INode(NodeKind::UnaryOp), operand_(std::move(operand)), op_kind_(op_kind) {
    SetLabel();
}

void UnaryOpNode::Accept(NodeVisitor &visitor) const{
    visitor.Visit(*this);
}

UnaryOpKind UnaryOpNode::GetOpKind() const noexcept {
    return op_kind_;
}

const std::unique_ptr<INode> &UnaryOpNode::GetOperand() const noexcept {
    return operand_;
}