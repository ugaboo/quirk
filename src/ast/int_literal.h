#pragma once

#include "node.h"

namespace quirk::ast {

class IntLiteral : public Expr {
public:
    IntLiteral(Context context) : Expr(context) {}

    uint64_t to_uint64() { return std::stoul(std::string(get_context().value)); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast