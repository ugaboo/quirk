#pragma once

#include "node.h"

namespace quirk::ast {

class AsgStmt : public Stmt {
    ExprPtr lvalue, rvalue, type_expr;

public:
    AsgStmt(Context context, ExprPtr& lvalue, ExprPtr& type_expr, ExprPtr& rvalue)
        : Stmt(context), lvalue(move(lvalue)), rvalue(move(rvalue)), type_expr(move(type_expr)) {}

    auto get_lvalue() { return lvalue.get(); }
    auto get_rvalue() { return rvalue.get(); }
    auto get_type_expr() { return type_expr.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast