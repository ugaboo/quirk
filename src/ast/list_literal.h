#pragma once

#include "node.h"

namespace quirk::ast {

class ListLiteral : public Expr {
    util::PtrList<Expr> exprs;

public:
    ListLiteral(Context context, std::vector<std::unique_ptr<Expr>>& exprs) : Expr(context)
    {
        for (auto& expr : exprs) {
            ListLiteral::exprs.push_back(move(expr));
        }
    }

    auto& get_exprs() { return exprs; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast