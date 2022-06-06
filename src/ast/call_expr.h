#pragma once

#include <memory>
#include <vector>

#include "../util/ptr_list.h"
#include "node.h"

namespace quirk::ast {

class CallExpr : public Expr {
    std::unique_ptr<Expr> designator;
    util::PtrList<Expr> args;

public:
    CallExpr(Context context, std::unique_ptr<Expr>& designator,
             std::vector<std::unique_ptr<Expr>>& args)
        : Expr(context), designator(move(designator))
    {
        for (auto& arg : args) {
            CallExpr::args.push_back(move(arg));
        }
    }

    auto get_designator() { return designator.get(); }
    auto& get_args() { return args; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast