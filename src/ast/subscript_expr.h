#pragma once
#include "node.h"

namespace quirk::ast {

class SubscriptExpr : public Expr {
    unique_ptr<Expr>         designator;
    vector<unique_ptr<Expr>> keys;

public:
    SubscriptExpr(Context context, unique_ptr<Expr>& designator, vector<unique_ptr<Expr>>& keys)
        : Expr(context), designator(move(designator)) {
        for (auto& key : keys) {
            SubscriptExpr::keys.push_back(move(key));
        }
    }

    auto get_designator() { return designator.get(); }
    auto count_keys() { return keys.size(); }
    auto get_key(size_t index) { return keys[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast