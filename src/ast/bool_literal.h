#pragma once

#include "node.h"

namespace quirk::ast {

class BoolLiteral : public Expr {
    bool value;

public:
    BoolLiteral(Context context) : Expr(context) { value = get_context().value == "True"; }

    auto get_value() { return value; }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast