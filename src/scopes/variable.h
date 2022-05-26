#pragma once

#include "../ast/asg_stmt.h"
#include "../ast/name_literal.h"
#include "declaration.h"

namespace quirk::scopes {

using namespace ast;

class Variable : public Declaration {
    AsgStmt* def;
    bool global = false;

public:
    Variable(AsgStmt* def) : def(def) {}

    auto get_def() { return def; }

    string_view get_name() override
    {
        return static_cast<NameLiteral*>(def->get_lvalue())->get_value();
    }

    auto make_global() { global = true; }
    auto is_global() { return global; }

    // void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes