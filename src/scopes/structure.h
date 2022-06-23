#pragma once

#include "../ast/struct_def_stmt.h"
#include "scope.h"

namespace quirk::scopes {

class Structure : public ProgObj {
public:
    Structure(Scope&& scope) : scope(std::move(scope)) {}

    Scope& get_scope() { return scope; }

    void accept(Visitor* visitor) override;

private:
    Scope scope;
};

} // namespace quirk::scopes