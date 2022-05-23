#pragma once
#include "name_literal.h"

namespace quirk::ast {

class MemberAccessExpr : public Expr {
    ExprPtr        designator;
    NameLiteralPtr selector;

public:
    MemberAccessExpr(Context context, ExprPtr& designator, NameLiteralPtr& selector)
        : Expr(context), designator(move(designator)), selector(move(selector))
    {
    }

    auto get_designator() { return designator.get(); }
    auto get_selector() { return selector.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast