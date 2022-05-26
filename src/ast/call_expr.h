#pragma once

#include "node.h"

namespace quirk::ast {

class CallExpr : public Expr {
    unique_ptr<Expr> designator;
    vector<unique_ptr<Expr>> args;

public:
    CallExpr(Context context, unique_ptr<Expr>& designator, vector<unique_ptr<Expr>>& args)
        : Expr(context), designator(move(designator))
    {
        for (auto& arg : args) {
            CallExpr::args.push_back(move(arg));
        }
    }

    auto get_designator() { return designator.get(); }
    auto count_args() { return args.size(); }
    auto get_arg(size_t index) { return args[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast