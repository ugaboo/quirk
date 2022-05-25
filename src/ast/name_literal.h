#pragma once
#include "node.h"

namespace quirk::ast {

class NameLiteral : public Expr {
public:
    NameLiteral(Context context) : Expr(context) {}

    NameLiteral() = delete;
    NameLiteral(NameLiteral&) = delete;
    NameLiteral(NameLiteral&&) = delete;

    auto get_value() { return get_context().value; }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast