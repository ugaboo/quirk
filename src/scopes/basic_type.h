#pragma once

#include "declaration.h"
#include "magic_enum.hpp"

namespace quirk::scopes {

enum class BasicTypeKind {
    Int64,
    Float64,
};

class BasicType : public Declaration {
private:
    BasicTypeKind kind;

public:
    BasicType() = delete;
    BasicType(BasicType&) = delete;
    BasicType(BasicType&&) = delete;

    BasicType(BasicTypeKind kind) : kind(kind) {}

    string_view get_name() override { return magic_enum::enum_name(kind); }

    BasicTypeKind get_kind() { return kind; }
};

} // namespace quirk::scopes