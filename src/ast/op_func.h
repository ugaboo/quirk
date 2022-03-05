#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class OpFunc : public Decl {
    string name;
    Decl* args[2];
    Decl* ret_type;

public:
    OpFunc(string name, Decl* arg1_type, Decl* arg2_type, Decl* ret_type) : name(name), ret_type(ret_type) {
        args[0] = arg1_type;
        args[1] = arg2_type;
    }
    OpFunc(string name, Decl* arg1_type, Decl* ret_type) : name(name), ret_type(ret_type) {
        args[0] = arg1_type;
        args[1] = nullptr;
    }

    auto get_name() { return name; }
    auto get_arg1_type() { return args[0]; }
    auto get_arg2_type() { return args[1]; }
    auto get_ret_type() { return ret_type; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast