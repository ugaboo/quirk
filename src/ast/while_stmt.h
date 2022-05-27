#pragma once

#include "node.h"

namespace quirk::ast {

class WhileStmt : public Stmt {
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmt>> stmts;

public:
    WhileStmt(Context context, std::unique_ptr<Expr>& condition,
              std::vector<std::unique_ptr<Stmt>>& stmts)
        : Stmt(context), condition(move(condition))
    {
        for (auto& stmnt : stmts) {
            WhileStmt::stmts.push_back(move(stmnt));
        }
    }

    auto get_condition() { return condition.get(); }
    auto count_stmts() { return stmts.size(); }
    auto get_stmt(size_t index) { return stmts[index].get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast