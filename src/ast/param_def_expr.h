#pragma once
#include "name_literal.h"

namespace quirk::ast {

class ParamDefExpr : public Expr {
    unique_ptr<NameLiteral> name;
    unique_ptr<Expr> type;

public:
    ParamDefExpr(unique_ptr<NameLiteral>& name, unique_ptr<Expr>& type)
        : Expr(name->get_context()), name(move(name)), type(move(type))
    {
    }

    auto get_name() { return name.get(); }
    auto get_type() { return type.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast