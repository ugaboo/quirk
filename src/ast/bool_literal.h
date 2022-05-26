#pragma once

#include "node.h"

namespace quirk::ast {

class BoolLiteral : public Expr {
public:
    BoolLiteral(Context context) : Expr(context) {}

    bool to_bool() { return get_context().value == "True"; }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast