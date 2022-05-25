#pragma once
#include "node.h"

namespace quirk::ast {

class ListLiteral : public Expr {
    vector<unique_ptr<Expr>> exprs;

public:
    ListLiteral(Context context, vector<unique_ptr<Expr>>& exprs) : Expr(context) {
        for (auto& expr : exprs) {
            ListLiteral::exprs.push_back(move(expr));
        }
    }

    auto count_exprs() { return exprs.size(); }
    auto get_expr(size_t index) { return exprs[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast