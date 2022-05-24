#pragma once

#include "name_literal.h"

namespace quirk::ast {

class Field;

class FieldDef : public Stmt {
    NameLiteralPtr name;
    ExprPtr        type;
    ExprPtr        init_expr;

public:
    FieldDef(NameLiteralPtr& name, ExprPtr& type, ExprPtr& init_expr)
        : Stmt(name->get_context()),
          name(move(name)),
          type(move(type)),
          init_expr(move(init_expr)) {}

    auto get_name() { return name.get(); }
    auto get_type() { return type.get(); }
    auto get_init_expr() { return init_expr.get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

using FieldDefPtr = unique_ptr<FieldDef>;

}  // namespace quirk::ast