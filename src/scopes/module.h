#pragma once

#include <filesystem>

#include "../ast/translation_unit.h"
#include "scope.h"

namespace quirk::scopes {

class Module : public ProgObj {
public:
    Module(Scope&& scope) : scope(std::move(scope)) {}

    Scope& get_scope() { return scope; }

    void accept(Visitor* visitor) override;

private:
    Scope scope;
};

} // namespace quirk::scopes