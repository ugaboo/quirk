#pragma once

#include "name_literal.h"

namespace quirk::ast {

class ParamDefExpr : public Expr {
    std::unique_ptr<NameLiteral> name;
    std::unique_ptr<Expr> type;

public:
    ParamDefExpr(std::unique_ptr<NameLiteral>& name, std::unique_ptr<Expr>& type)
        : Expr(name->get_context()), name(move(name)), type(move(type))
    {
    }

    auto get_name() { return name.get(); }
    auto get_type() { return type.get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast