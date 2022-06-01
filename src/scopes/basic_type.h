#pragma once

#include "declaration.h"
#include "magic_enum.hpp"

namespace quirk::scopes {

enum class BasicTypeKind {
    Int,
    Float,
};

class BasicType : public Declaration {
private:
    BasicTypeKind kind;

public:
    BasicType(BasicTypeKind kind) : kind(kind) {}

    std::string_view get_name() override { return magic_enum::enum_name(kind); }

    BasicTypeKind get_kind() { return kind; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes