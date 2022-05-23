#pragma once
#include "node.h"
#include "param_def_expr.h"

namespace quirk::ast {

class Function;

class FuncDefStmt : public Stmt {
    Context                 context;
    vector<ParamDefExprPtr> params;
    ExprPtr                 ret_type_expr;
    vector<StmtPtr>         stmts;

public:
    FuncDefStmt(Context                  context,
                vector<ParamDefExprPtr>& params,
                ExprPtr&                 ret_type_expr,
                vector<StmtPtr>&         stmts)
        : Stmt(context), ret_type_expr(move(ret_type_expr))
    {
        for (auto& param : params) {
            FuncDefStmt::params.push_back(move(param));
        }
        for (auto& stmt : stmts) {
            FuncDefStmt::stmts.push_back(move(stmt));
        }
    }

    auto get_name() { return context.value; }
    auto count_params() { return params.size(); }
    auto get_param(size_t index) { return params[index].get(); }
    auto get_ret_type_expr() { return ret_type_expr.get(); }
    auto count_stmts() { return stmts.size(); }
    auto get_stmt(size_t index) { return stmts[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast