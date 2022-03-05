#pragma once
#include <map>
#include "field_def.h"

namespace quirk::ast {

class Field : public Decl {
    FieldDef* source;

public:
    Field(FieldDef* source) : source(source) {}

    auto get_name() { return source->get_name(); }
    auto get_source() { return source; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast