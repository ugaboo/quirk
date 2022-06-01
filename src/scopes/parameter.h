#pragma once

#include "../ast/param_def_expr.h"
#include "declaration.h"

namespace quirk::scopes {

class Parameter : public Declaration {
    ast::ParamDefExpr* def;

public:
    Parameter(ast::ParamDefExpr* def) : def(def) {}

    auto get_def() { return def; }
    std::string_view get_name() override { return def->get_name()->get_value(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes