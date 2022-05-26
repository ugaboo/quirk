#pragma once

#include "name_literal.h"

namespace quirk::ast {

class FieldDefStmt : public Stmt {
    unique_ptr<NameLiteral> name;
    unique_ptr<Expr> type;
    unique_ptr<Expr> init_expr;

public:
    FieldDefStmt(unique_ptr<NameLiteral>& name, unique_ptr<Expr>& type, unique_ptr<Expr>& init_expr)
        : Stmt(name->get_context()), name(move(name)), type(move(type)), init_expr(move(init_expr))
    {
    }

    auto get_name() { return name.get(); }
    auto get_type() { return type.get(); }
    auto get_init_expr() { return init_expr.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast