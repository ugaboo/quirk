#pragma once

#include "../ast/func_def_stmt.h"
#include "scope.h"

namespace quirk::scopes {

using namespace ast;

class Function : public Scope, public Declaration {
    FuncDefStmt* def = nullptr;

public:
    Function(FuncDefStmt* def) : def(def) {}

    string_view get_name() override { return def->get_name()->get_value(); }

    auto get_def() { return def; }
};

} // namespace quirk::scopes