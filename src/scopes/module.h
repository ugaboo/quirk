#pragma once

#include <filesystem>

#include "../ast/translation_unit.h"
#include "scope.h"

namespace quirk::scopes {

class Module : public Declaration {
    ast::TranslationUnit* def;
    Scope scope;

    std::string name;

public:
    Module(ast::TranslationUnit* def, Scope& global_scope) : def(def), scope(global_scope)
    {
        auto path = std::filesystem::path(def->get_filename());
        name = path.stem().string();
    }

    std::string_view get_name() override { return std::string_view(name); }

    auto get_def() { return def; }
    Scope& get_scope() { return scope; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes