#pragma once
#include "name_literal.h"

namespace quirk::ast {

class ParamDefExpr : public Expr {
    NameLiteralPtr name;
    ExprPtr        type;

public:
    ParamDefExpr(NameLiteralPtr& name, ExprPtr& type)
        : Expr(name->get_context()), name(move(name)), type(move(type))
    {
    }

    auto get_name() { return name->get_value(); }
    auto get_type() { return type.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

using ParamDefExprPtr = unique_ptr<ParamDefExpr>;

}  // namespace quirk::ast