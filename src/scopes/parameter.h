#pragma once
#include "ast/parameter_def.h"

namespace quirk::scopes {

class Parameter : public Decl {
    ParameterDef* def;

public:
    Parameter(ParameterDef* def) : def(def) {}

    auto get_name() { return def->get_name(); }
    auto get_def() { return def; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast