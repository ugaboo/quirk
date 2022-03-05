#pragma once
#include "compilation_error.h"
#include "prog_obj.h"

namespace quirk::ast {

class FloatLiteral : public Expr {
    Context context;
    double value;

public:
    FloatLiteral(Context&& context) : context(context) {
        string str(context.value.data(), context.value.size());
        value = strtod(str.c_str(), nullptr);
        if (errno == ERANGE) {
            throw CompilationError::ConstantTooLarge;
        }
    }

    auto get_value() { return value; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast