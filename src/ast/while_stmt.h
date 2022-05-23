#pragma once
#include "node.h"

namespace quirk::ast {

class WhileStmt : public Stmt {
    ExprPtr         condition;
    vector<StmtPtr> stmts;

public:
    WhileStmt(Context context, ExprPtr& condition, vector<StmtPtr>& stmts)
        : Stmt(context), condition(move(condition))
    {
        for (auto& stmnt : stmts) {
            WhileStmt::stmts.push_back(move(stmnt));
        }
    }

    auto get_condition() { return condition.get(); }
    auto count_stmts() { return stmts.size(); }
    auto get_stmt(size_t index) { return stmts[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast