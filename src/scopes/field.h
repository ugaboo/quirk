#pragma once

#include "ast/field_def.h"
#include "declaration.h"

namespace quirk::scopes {

using namespace ast;

class Field : public Declaration {
    FieldDef* def;

public:
    Field(FieldDef* def) : def(def) {}

    auto get_def() { return def; }

    string_view get_name() override { return def->get_name()->get_value(); }
};

}  // namespace quirk::scopes