#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class Int64Type : public Decl {
    Int64Type() {}

public:
    static auto get_instance() {
        static Int64Type instance;
        return &instance;
    }

    void accept(Visitor* visitor) override;
};

class Float64Type : public Decl {
    Float64Type() {}

public:
    static auto get_instance() {
        static Float64Type instance;
        return &instance;
    }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast