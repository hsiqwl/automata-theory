#include "unary_op.h"

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

UnaryOpNode::UnaryOpNode(UnaryOpKind op_kind, std::unique_ptr<Node> &&operand)
    : Node(NodeKind::UnaryOp), operand_(std::move(operand)), op_kind_(op_kind) {
    SetLabel();
}