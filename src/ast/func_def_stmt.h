#pragma once

#include <vector>

#include "../util/ptr_list.h"
#include "param_def_expr.h"

namespace quirk::ast {

class FuncDefStmt : public Stmt {
    std::unique_ptr<NameLiteral> name;
    util::PtrList<ParamDefExpr> params;
    std::unique_ptr<Expr> ret_type_expr;
    util::PtrList<Stmt> stmts;

public:
    FuncDefStmt(Context context, std::unique_ptr<NameLiteral>& name,
                std::vector<std::unique_ptr<ParamDefExpr>>& params,
                std::unique_ptr<Expr>& ret_type_expr, std::vector<std::unique_ptr<Stmt>>& stmts)
        : Stmt(context), name(move(name)), params(params), ret_type_expr(move(ret_type_expr)),
          stmts(stmts)
    {
    }

    auto get_name() { return name.get(); }
    auto& get_params() { return params; }
    auto get_ret_type_expr() { return ret_type_expr.get(); }
    auto& get_stmts() { return stmts; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast