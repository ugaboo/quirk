#pragma once

#include "../ast/struct_def_stmt.h"
#include "scope.h"

namespace quirk::scopes {

class Structure : public Declaration {
    ast::StructDefStmt* def;
    Scope scope;

public:
    Structure(ast::StructDefStmt* def, Scope& parent_scope) : def(def), scope(parent_scope) {}

    std::string_view get_name() override { return def->get_name()->get_value(); }

    auto get_def() { return def; }

    Scope& get_scope() { return scope; }
};

} // namespace quirk::scopes