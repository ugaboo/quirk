#pragma once

#include "../ast/field_def_stmt.h"
#include "declaration.h"

namespace quirk::scopes {

class Field : public Declaration {
    ast::FieldDefStmt* def;

public:
    Field(ast::FieldDefStmt* def) : def(def) {}

    auto get_def() { return def; }

    std::string_view get_name() override { return def->get_name()->get_value(); }
};

} // namespace quirk::scopes