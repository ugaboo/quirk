#pragma once

#include "../util/ptr_list.h"
#include "node.h"

namespace quirk::ast {

class IfStmt : public Stmt {
public:
    class Branch {
        std::unique_ptr<Expr> condition;
        util::PtrList<Stmt> stmts;

    public:
        Branch(std::unique_ptr<Expr>& condition, std::vector<std::unique_ptr<Stmt>>& stmts)
            : condition(move(condition))
        {
            for (auto& stmt : stmts) {
                Branch::stmts.push_back(move(stmt));
            }
        }

        auto get_condition() { return condition.get(); }
        auto& get_stmts() { return stmts; }
    };

private:
    util::PtrList<Branch> branches;
    util::PtrList<Stmt> else_stmts;

public:
    IfStmt(Context context, std::vector<std::unique_ptr<Branch>>& branches,
           std::vector<std::unique_ptr<Stmt>>& else_stmts)
        : Stmt(context)
    {
        for (auto& branch : branches) {
            IfStmt::branches.push_back(move(branch));
        }
        for (auto& stmt : else_stmts) {
            IfStmt::else_stmts.push_back(move(stmt));
        }
    }

    auto& get_branches() { return branches; }
    auto& get_else_stmts() { return else_stmts; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast