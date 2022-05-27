#pragma once

#include <memory>

#include "node.h"

namespace quirk::ast {

class AsgStmt : public Stmt {
    std::unique_ptr<Expr> lvalue;
    std::unique_ptr<Expr> type_expr;
    std::unique_ptr<Expr> rvalue;

public:
    AsgStmt(Context context, std::unique_ptr<Expr>& lvalue, std::unique_ptr<Expr>& type_expr,
            std::unique_ptr<Expr>& rvalue)
        : Stmt(context), lvalue(move(lvalue)), rvalue(move(rvalue)), type_expr(move(type_expr))
    {
    }

    auto get_lvalue() { return lvalue.get(); }
    auto get_rvalue() { return rvalue.get(); }
    auto get_type_expr() { return type_expr.get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast