#pragma once
#include "asg_stmt.h"
#include "name_literal.h"

namespace quirk::ast {

class Variable : public Decl {
    AsgStmt* def;
    bool global = false;

public:
    Variable(AsgStmt* def) : def(def) {}

    auto get_name() {
        auto name = static_cast<NameLiteral*>(def->get_lvalue());
        return name->get_value();
    }
    auto get_def() { return def; }
    auto make_global() { global = true; }
    auto is_global() { return global; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast