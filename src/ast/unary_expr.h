#pragma once

#include <memory>

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
    std::unique_ptr<Expr> expr;

public:
    UnaryExpr(Context context, UnaryOpKind kind, std::unique_ptr<Expr>& expr)
        : Expr(context), kind(kind), expr(move(expr))
    {
    }

    auto get_kind() { return kind; }
    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast