#pragma once

#include "node.h"

namespace quirk::ast {

class ReturnStmt : public Stmt {
    std::unique_ptr<Expr> expr;

public:
    ReturnStmt(Context context, std::unique_ptr<Expr>& expr) : Stmt(context), expr(move(expr)) {}

    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast