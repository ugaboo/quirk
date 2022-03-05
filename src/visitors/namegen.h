#pragma once
#include <stdexcept>
#include "ast/visitor.h"
#include "type_inference.h"

namespace quirk {

using std::string;

class NameGen : public ast::Visitor {
    string name;

public:
    NameGen(ast::ProgObj* item) {
        item->accept(this);
        assert(name != "");
    }

    auto get_name() { return name; }

    void visit(ast::OpFunc* item) override {
        name = item->get_name();
        NameGen arg1(item->get_arg1_type());
        name += "@" + arg1.get_name();
        if (item->get_arg2_type() != nullptr) {
            NameGen arg2(item->get_arg2_type());
            name += "@" + arg2.get_name();
        }
    }

    void visit(ast::BinaryExpr* item) override {
        switch (item->get_kind()) {
        case ast::BinaryExpr::Kind::Add:
            name = "__add__";
            break;
        default:
            throw std::logic_error("Not implemented");
        }

        TypeInference ti_left(item->get_left());
        NameGen left(ti_left.get_type());
        TypeInference ti_right(item->get_right());
        NameGen right(ti_right.get_type());
        name += "@" + left.get_name() + "@" + right.get_name();
    }

    void visit(ast::Int64Type* item) override { name = "Int"; }

    void visit(ast::Float64Type* item) override { name = "Float"; }
};

}  // namespace quirk