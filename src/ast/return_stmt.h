#pragma once
#include "node.h"

namespace quirk::ast {

class ReturnStmt : public Stmt {
    ExprPtr expr;

public:
    ReturnStmt(Context context, ExprPtr& expr) : Stmt(context), expr(move(expr)) {}

    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast