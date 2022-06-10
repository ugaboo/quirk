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

    BasicType(BasicTypeKind kind) : kind(kind) {}

public:
    BasicType* get_int() {
        static BasicType type(BasicTypeKind::Int);
        return &type;
    }

    BasicType* get_float() {
        static BasicType type(BasicTypeKind::Float);
        return &type;
    }

    std::string_view get_name() override { return magic_enum::enum_name(kind); }

    BasicTypeKind get_kind() { return kind; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes