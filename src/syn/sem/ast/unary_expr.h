#pragma once
#include "node.h"

namespace quirk::ast {

class UnaryExpr : public Expr {
public:
    enum class Kind {
        Not,
        BitNot,
        Plus,
        Minus,
    };

private:
    Kind kind;
    unique_ptr<Expr> expr;

public:
    UnaryExpr(Kind kind, unique_ptr<Expr>& expr) : kind(kind), expr(move(expr)) {}

    auto get_kind() { return kind; }
    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast