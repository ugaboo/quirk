#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class Field;

class FieldDef : public ProgObj {
    Field* decl = nullptr;

    Context context;
    unique_ptr<Expr> type;
    unique_ptr<Expr> init_expr;

public:
    FieldDef(Context& context, unique_ptr<Expr>& type, unique_ptr<Expr>& init_expr)
        : context(context), type(move(type)), init_expr(move(init_expr)) {}

    auto get_name() { return context.value; }
    auto get_type() { return type.get(); }
    auto get_init_expr() { return init_expr.get(); }
    auto get_decl() { return decl; }
    void set_decl(Field* decl) { FieldDef::decl = decl; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast