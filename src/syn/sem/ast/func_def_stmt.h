#pragma once
#include "node.h"
#include "parameter_def.h"

namespace quirk::ast {

class Function;

class FuncDefStmt : public Stmt {
    Function* decl = nullptr;

    Context context;
    vector<unique_ptr<ParameterDef>> params;
    unique_ptr<Expr> ret_type_expr;
    vector<unique_ptr<Stmt>> stmts;

public:
    FuncDefStmt(Context& context,
                vector<unique_ptr<ParameterDef>>& params,
                unique_ptr<Expr>& ret_type_expr,
                vector<unique_ptr<Stmt>>& stmts)
        : context(move(context)), ret_type_expr(move(ret_type_expr)) {
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
    auto get_decl() { return decl; }
    void set_decl(Function* decl) { FuncDefStmt::decl = decl; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast