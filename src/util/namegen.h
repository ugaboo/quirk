#pragma once
#include "type_inference.h"
#include "visitor.h"
#include <stdexcept>

namespace quirk {

using std::string;

class NameGen : public Visitor {
    string name;

public:
    NameGen(ast::Node* node)
    {
        node->accept(this);
        assert(name != "");
    }

    auto get_name() { return name; }

    void visit(ast::OpFunc* node) override
    {
        name = node->get_name();
        NameGen arg1(node->get_arg1_type());
        name += "@" + arg1.get_name();
        if (node->get_arg2_type() != nullptr) {
            NameGen arg2(node->get_arg2_type());
            name += "@" + arg2.get_name();
        }
    }

    void visit(ast::BinaryExpr* node) override
    {
        switch (node->get_kind()) {
        case ast::BinaryExpr::Kind::Add:
            name = "__add__";
            break;
        default:
            throw std::logic_error("Not implemented");
        }

        TypeInference ti_left(node->get_left());
        NameGen left(ti_left.get_type());
        TypeInference ti_right(node->get_right());
        NameGen right(ti_right.get_type());
        name += "@" + left.get_name() + "@" + right.get_name();
    }

    void visit(ast::Int64Type* node) override { name = "Int"; }

    void visit(ast::Float64Type* node) override { name = "Float"; }
};

} // namespace quirk