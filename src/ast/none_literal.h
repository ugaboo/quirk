#pragma once

#include "node.h"

namespace quirk::ast {

class NoneLiteral : public Expr {
public:
    NoneLiteral(Context context) : Expr(context) {}

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast