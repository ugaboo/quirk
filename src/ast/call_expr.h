#pragma once

#include <memory>
#include <vector>

#include "node.h"

namespace quirk::ast {

class CallExpr : public Expr {
    std::unique_ptr<Expr> designator;
    std::vector<std::unique_ptr<Expr>> args;

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
    auto count_args() { return args.size(); }
    auto get_arg(size_t index) { return args[index].get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast