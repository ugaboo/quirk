#pragma once
#include "node.h"

namespace quirk::ast {

class CallExprStmt : public Expr, public Stmt {
    unique_ptr<Expr> designator;
    vector<unique_ptr<Expr>> args;

public:
    CallExprStmt(unique_ptr<Expr>& designator, vector<unique_ptr<ast::Expr>>& args) : designator(move(designator)) {
        for (auto& arg : args) {
            CallExprStmt::args.push_back(move(arg));
        }
    }

    auto get_designator() { return designator.get(); }
    auto count_args() { return args.size(); }
    auto get_arg(size_t index) { return args[index].get(); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast