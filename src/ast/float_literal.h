#pragma once
#include "../compilation_error.h"
#include "node.h"

namespace quirk::ast {

class FloatLiteral : public Expr {
public:
    FloatLiteral(Context context) : Expr(context) {}

    double to_double()
    {
        string str(get_context().value);
        double value = strtod(str.c_str(), nullptr);
        if (errno == ERANGE) {
            throw CompilationError::ConstantTooLarge;
        }
        return value;
    }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast