#pragma once

#include "../ast/translation_unit.h"
#include "scope.h"

namespace quirk::scopes {

class Module : public Scope {
    ast::TranslationUnit* def;

public:
    Module(ast::TranslationUnit* def) : def(def) {}

    auto get_def() { return def; }
};

} // namespace quirk::scopes