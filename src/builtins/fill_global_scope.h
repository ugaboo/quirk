#pragma once

#include <memory>

#include "../scopes/visitor.h"

namespace quirk::builtins {

void fill_global_scope(scopes::Scope& global_scope)
{
    using namespace scopes;

    global_scope.insert("Int", std::make_unique<BasicType>(BasicTypeKind::Int));
    global_scope.insert("Float", std::make_unique<BasicType>(BasicTypeKind::Float));
}

} // namespace quirk::builtins