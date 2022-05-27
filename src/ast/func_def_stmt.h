#pragma once

#include "param_def_expr.h"

namespace quirk::ast {

class FuncDefStmt : public Stmt {
    std::unique_ptr<NameLiteral> name;
    std::vector<std::unique_ptr<ParamDefExpr>> params;
    std::unique_ptr<Expr> ret_type_expr;
    std::vector<std::unique_ptr<Stmt>> stmts;

public:
    FuncDefStmt(Context context, std::unique_ptr<NameLiteral>& name,
                std::vector<std::unique_ptr<ParamDefExpr>>& params,
                std::unique_ptr<Expr>& ret_type_expr, std::vector<std::unique_ptr<Stmt>>& stmts)
        : Stmt(context), name(move(name)), ret_type_expr(move(ret_type_expr))
    {
        for (auto& param : params) {
            FuncDefStmt::params.push_back(move(param));
        }
        for (auto& stmt : stmts) {
            FuncDefStmt::stmts.push_back(move(stmt));
        }
    }

    auto get_name() { return name.get(); }
    auto count_params() { return params.size(); }
    auto get_param(size_t index) { return params[index].get(); }
    auto get_ret_type_expr() { return ret_type_expr.get(); }
    auto count_stmts() { return stmts.size(); }
    auto get_stmt(size_t index) { return stmts[index].get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast