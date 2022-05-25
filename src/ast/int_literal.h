#pragma once
#include "../compilation_error.h"
#include "node.h"

namespace quirk::ast {

class IntLiteral : public Expr {
    uint64_t value;

public:
    IntLiteral(Context context) : Expr(context)
    {
        string str(context.value.data(), context.value.size());
        value = strtoull(str.c_str(), nullptr, 10);
        if (errno == ERANGE) {
            throw CompilationError::ConstantTooLarge;
        }
    }

    auto get_value() { return value; }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast