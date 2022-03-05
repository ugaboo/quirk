#pragma once
#include "parameter_def.h"

namespace quirk::ast {

class Parameter : public Decl {
    ParameterDef* def;

public:
    Parameter(ParameterDef* def) : def(def) {}

    auto get_name() { return def->get_name(); }
    auto get_def() { return def; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast