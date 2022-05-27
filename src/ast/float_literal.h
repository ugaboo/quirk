#pragma once

#include "node.h"

namespace quirk::ast {

class FloatLiteral : public Expr {
public:
    FloatLiteral(Context context) : Expr(context) {}

    double to_double() { return std::stod(std::string(get_context().value)); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast