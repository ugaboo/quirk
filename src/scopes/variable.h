#pragma once

#include "../ast/asg_stmt.h"
#include "../ast/name_literal.h"
#include "declaration.h"

namespace quirk::scopes {

class Variable : public Declaration {
    ast::AsgStmt* def;
    bool global = false;

public:
    Variable(ast::AsgStmt* def) : def(def) {}

    auto get_def() { return def; }

    std::string_view get_name() override
    {
        return static_cast<ast::NameLiteral*>(def->get_lvalue())->get_value();
    }

    auto make_global() { global = true; }
    auto is_global() { return global; }

    // void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes