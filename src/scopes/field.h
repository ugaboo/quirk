#pragma once
#include <map>
#include "ast/field_def.h"

namespace quirk::scopes {

class Field : public Decl {
    FieldDef* source;

public:
    Field(FieldDef* source) : source(source) {}

    auto get_name() { return source->get_name(); }
    auto get_source() { return source; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast