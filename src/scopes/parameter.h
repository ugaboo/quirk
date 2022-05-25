#pragma once

#include "ast/param_def_expr.h"
#include "declaration.h"

namespace quirk::scopes {

using namespace ast;

class Parameter : public Declaration {
    ParamDefExpr* def;

public:
    Parameter(ParamDefExpr* def) : def(def) {}

    auto get_def() { return def; }

    string_view get_name() override { return def->get_name()->get_value(); }

    // void accept(Visitor* visitor) override;
};

}  // namespace quirk::scopes