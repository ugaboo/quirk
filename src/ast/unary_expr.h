#pragma once
#include "node.h"

namespace quirk::ast {

enum class UnaryOpKind {
    Not,
    BitNot,
    Plus,
    Minus,
};

class UnaryExpr : public Expr {
    UnaryOpKind kind;
    ExprPtr     expr;

public:
    UnaryExpr(Context context, UnaryOpKind kind, ExprPtr& expr)
        : Expr(context), kind(kind), expr(move(expr))
    {
    }

    auto get_kind() { return kind; }
    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast