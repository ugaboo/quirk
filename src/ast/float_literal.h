#pragma once
#include "../compilation_error.h"
#include "node.h"

namespace quirk::ast {

class FloatLiteral : public Expr {
    double value;

public:
    FloatLiteral(Context context) : Expr(context)
    {
        string str(context.value.data(), context.value.size());
        value = strtod(str.c_str(), nullptr);
        if (errno == ERANGE) {
            throw CompilationError::ConstantTooLarge;
        }
    }

    auto get_value() { return value; }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast