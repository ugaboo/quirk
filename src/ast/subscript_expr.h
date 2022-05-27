#pragma once

#include "node.h"

namespace quirk::ast {

class SubscriptExpr : public Expr {
    std::unique_ptr<Expr> designator;
    std::vector<std::unique_ptr<Expr>> keys;

public:
    SubscriptExpr(Context context, std::unique_ptr<Expr>& designator,
                  std::vector<std::unique_ptr<Expr>>& keys)
        : Expr(context), designator(move(designator))
    {
        for (auto& key : keys) {
            SubscriptExpr::keys.push_back(move(key));
        }
    }

    auto get_designator() { return designator.get(); }
    auto count_keys() { return keys.size(); }
    auto get_key(size_t index) { return keys[index].get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast