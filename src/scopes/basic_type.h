#pragma once

#include "magic_enum.hpp"
#include "prog_obj.h"

namespace quirk::scopes {

enum class BasicTypeKind {
    Int,
    Float,
};

class BasicType : public ProgObj {
public:
    BasicType(BasicTypeKind kind) : kind(kind) {}

    BasicTypeKind get_kind() { return kind; }

    void accept(Visitor* visitor) override;

private:
    BasicTypeKind kind;
};

} // namespace quirk::scopes