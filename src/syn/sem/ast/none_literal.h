#pragma once
#include "node.h"

namespace quirk::ast {

class NoneLiteral : public Expr {
    Context context;

public:
    NoneLiteral(Context&& context) : context(context) {}

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast