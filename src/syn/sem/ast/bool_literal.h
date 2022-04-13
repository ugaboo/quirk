#pragma once
#include "node.h"

namespace quirk::ast {

class BoolLiteral : public Expr {
    Context context;
    bool value;

public:
    BoolLiteral(Context&& context) : context(context) { value = context.value == "True"; }

    auto get_value() { return value; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast