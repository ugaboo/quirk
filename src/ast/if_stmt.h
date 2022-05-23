#pragma once
#include "node.h"

namespace quirk::ast {

class IfStmt : public Stmt {
    using Condition = unique_ptr<ast::Expr>;
    using Statements = vector<unique_ptr<ast::Stmt>>;
    using Branch = std::pair<Condition, Statements>;

    vector<Branch> branches;
    Statements     else_stmts;

public:
    IfStmt(Context context, vector<Branch>& branches, vector<unique_ptr<Stmt>>& else_stmts)
        : Stmt(context)
    {
        for (auto& branch : branches) {
            IfStmt::branches.emplace_back();
            IfStmt::branches.back().first = move(branch.first);
            for (auto& stmt : branch.second) {
                IfStmt::branches.back().second.push_back(move(stmt));
            }
        }
        for (auto& stmt : else_stmts) {
            IfStmt::else_stmts.push_back(move(stmt));
        }
    }

    auto count_branches() { return branches.size(); }
    auto get_condition(size_t branch_index) { return branches[branch_index].first.get(); }
    auto count_branch_stmts(size_t branch_index) { return branches[branch_index].second.size(); }
    auto get_branch_stmt(size_t branch_index, size_t stmt_index)
    {
        return branches[branch_index].second[stmt_index].get();
    }
    auto count_else_stmts() { return else_stmts.size(); }
    auto get_else_stmt(size_t index) { return else_stmts[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast