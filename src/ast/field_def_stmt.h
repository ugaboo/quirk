#pragma once

#include "name_literal.h"

namespace quirk::ast {

class FieldDefStmt : public Stmt {
    std::unique_ptr<NameLiteral> name;
    std::unique_ptr<Expr> type;
    std::unique_ptr<Expr> init_expr;

public:
    FieldDefStmt(std::unique_ptr<NameLiteral>& name, std::unique_ptr<Expr>& type,
                 std::unique_ptr<Expr>& init_expr)
        : Stmt(name->get_context()), name(move(name)), type(move(type)), init_expr(move(init_expr))
    {
    }

    auto get_name() { return name.get(); }
    auto get_type() { return type.get(); }
    auto get_init_expr() { return init_expr.get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast