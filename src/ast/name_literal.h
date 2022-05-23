#pragma once
#include "node.h"

namespace quirk::ast {

class NameLiteral : public Expr {
public:
    NameLiteral(Context context) : Expr(context) {}

    auto get_value() { return get_context().value; }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

using NameLiteralPtr = unique_ptr<NameLiteral>;

}  // namespace quirk::ast