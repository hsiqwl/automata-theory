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

UnaryOpNode::UnaryOpNode(UnaryOpKind op_kind, INode* operand)
    : INode(NodeKind::UnaryOp), operand_(operand), op_kind_(op_kind) {
    SetLabel();
}

void UnaryOpNode::Accept(NodeVisitor &visitor) {
    operand_->Accept(visitor);
    visitor.Visit(*this);
}