#pragma once

#include "node.h"

namespace quirk::ast {

class SubscriptExpr : public Expr {
    std::unique_ptr<Expr> designator;
    util::PtrList<Expr> keys;

public:
    SubscriptExpr(Context context, std::unique_ptr<Expr>& designator,
                  std::vector<std::unique_ptr<Expr>>& keys)
        : Expr(context), designator(move(designator)), keys(keys)
    {
    }

    auto get_designator() { return designator.get(); }
    auto& get_keys() { return keys; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast