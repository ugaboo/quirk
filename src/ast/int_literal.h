#pragma once
#include "../compilation_error.h"
#include "node.h"

namespace quirk::ast {

class IntLiteral : public Expr {
public:
    IntLiteral(Context context) : Expr(context) {}

    uint64_t to_int64()
    {
        string str(get_context().value);
        uint64_t value = strtoull(str.c_str(), nullptr, 10);
        if (errno == ERANGE) {
            throw CompilationError::ConstantTooLarge;
        }
        return value;
    }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast