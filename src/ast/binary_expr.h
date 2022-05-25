#pragma once

#include "node.h"

namespace quirk::ast {

enum class BinaryOpKind {
    Or,
    And,
    Less,
    Greater,
    Equal,
    LessOrEqual,
    GreaterOrEqual,
    NotEqual,
    BitOr,
    BitXor,
    BitAnd,
    LeftShift,
    RightShift,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    IntDiv,
    Power,
};

class BinaryExpr : public Expr {
    BinaryOpKind kind;
    unique_ptr<Expr> left, right;

public:
    BinaryExpr(Context context, BinaryOpKind kind, unique_ptr<Expr>& left, unique_ptr<Expr>& right)
        : Expr(context), kind(kind), left(move(left)), right(move(right))
    {
    }

    auto get_kind() { return kind; }
    auto get_left() { return left.get(); }
    auto get_right() { return right.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast