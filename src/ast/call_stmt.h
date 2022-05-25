#pragma once

#include "call_expr.h"

namespace quirk::ast {

class CallStmt : public Stmt {
    unique_ptr<CallExpr> expr;

public:
    CallStmt(unique_ptr<CallExpr>& expr) : Stmt(expr->get_context()), expr(move(expr)) {}

    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast