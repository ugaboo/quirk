#pragma once
#include "name_literal.h"

namespace quirk::ast {

class MemberAccessExpr : public Expr {
    unique_ptr<Expr> designator;
    unique_ptr<NameLiteral> selector;

public:
    MemberAccessExpr(unique_ptr<Expr>& designator, unique_ptr<NameLiteral>& selector)
        : designator(move(designator)), selector(move(selector)) {}

    auto get_designator() { return designator.get(); }
    auto get_selector() { return selector.get(); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast