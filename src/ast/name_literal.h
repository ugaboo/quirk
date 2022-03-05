#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class NameLiteral : public Expr {
    Decl* decl = nullptr;

    Context context;

public:
    NameLiteral(Context&& context) : context(context) {}

    auto get_value() { return context.value; }
    auto get_decl() { return decl; }
    auto set_decl(Decl* decl) { NameLiteral::decl = decl; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast