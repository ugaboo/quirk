#pragma once

#include "../ast/func_def_stmt.h"
#include "scope.h"

namespace quirk::scopes {

class Function : public Declaration {
    ast::FuncDefStmt* def;
    Scope scope;

public:
    Function(Function&) = delete;

    Function(ast::FuncDefStmt* def, Scope& parent_scope) : def(def), scope(parent_scope) {}

    std::string_view get_name() override { return def->get_name()->get_value(); }

    auto get_def() { return def; }

    Scope& get_scope() { return scope; }
};

} // namespace quirk::scopes