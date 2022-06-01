#pragma once

#include "../ast/translation_unit.h"
#include "scope.h"

namespace quirk::scopes {

class Module : public Declaration {
    ast::TranslationUnit* def;
    Scope scope;

public:
    Module(ast::TranslationUnit* def, Scope& global_scope) : def(def), scope(global_scope) {}

    std::string_view get_name() override
    {
        // TODO: extract module name from filename
        return def->get_filename();
    }

    auto get_def() { return def; }
    Scope& get_scope() { return scope; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes