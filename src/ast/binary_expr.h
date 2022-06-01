#pragma once

#include <memory>

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
    std::unique_ptr<Expr> left, right;

public:
    BinaryExpr(Context context, BinaryOpKind kind, std::unique_ptr<Expr>& left,
               std::unique_ptr<Expr>& right)
        : Expr(context), kind(kind), left(move(left)), right(move(right))
    {
    }

    auto get_kind() { return kind; }
    auto get_left() { return left.get(); }
    auto get_right() { return right.get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast