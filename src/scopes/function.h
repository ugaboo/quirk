#pragma once

#include "../ast/func_def_stmt.h"
#include "scope.h"

namespace quirk::scopes {

class Function : public Type {
public:
    Function(Scope&& scope) : scope(std::move(scope)) {}

    Scope& get_scope() { return scope; }

    void accept(Visitor* visitor) override;

private:
    Scope scope;
};

} // namespace quirk::scopes