#pragma once

#include "../ast/struct_def_stmt.h"
#include "scope.h"

namespace quirk::scopes {

class Structure : public Scope, public Declaration {
    ast::StructDefStmt* def;

public:
    // Structure() = delete;
    // Structure(Structure&) = delete;
    // Structure(Structure&&) = delete;

    Structure(ast::StructDefStmt* def, Scope* parent) : Scope(parent), def(def) {}

    std::string_view get_name() override { return def->get_name()->get_value(); }

    auto get_def() { return def; }

    // void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes