#pragma once
#include "node.h"

namespace quirk::ast {

class BasicType : public Decl {
public:
    enum class Kind {
        Int64,
        Float64,
    };

private:
    Kind kind;

public:
};

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