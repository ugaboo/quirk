#pragma once
#include "name_literal.h"

namespace quirk::ast {

class Parameter;

class ParameterDef : public Node {
    Parameter* decl = nullptr;

    Context context;
    unique_ptr<Expr> type;

public:
    ParameterDef(Context& context, unique_ptr<Expr>& type) : context(context), type(move(type)) {}

    auto get_name() { return context.value; }
    auto get_type() { return type.get(); }
    auto get_decl() { return decl; }
    auto set_decl(Parameter* decl) { ParameterDef::decl = decl; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast