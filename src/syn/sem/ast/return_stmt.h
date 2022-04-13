#pragma once
#include "node.h"

namespace quirk::ast {

class ReturnStmt : public Stmt {
    unique_ptr<Expr> expr;

public:
    ReturnStmt(unique_ptr<Expr>& expr) : expr(move(expr)) {}

    auto get_expr() { return expr.get(); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast