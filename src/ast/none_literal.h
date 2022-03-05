#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class NoneLiteral : public Expr {
    Context context;

public:
    NoneLiteral(Context&& context) : context(context) {}

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast