#pragma once
#include "ast/headers.h"
#include "scanner/scanner.h"
#include <functional>
#include <memory>
#include <vector>

namespace quirk {

using std::unique_ptr;
using std::vector;

using namespace ast;

class Parser {
    Scanner scanner;

public:
    Parser(string filename);

    bool parse(vector<unique_ptr<Stmt>>& stmts);

private:
    bool are_expressions(vector<unique_ptr<Expr>>& result);
    bool are_fields(vector<FieldDefPtr>& result);
    bool are_parameters(vector<ParamDefExprPtr>& result);
    bool are_statements(vector<unique_ptr<Stmt>>& result);
    bool is_and(unique_ptr<Expr>& result);
    bool is_arith(unique_ptr<Expr>& result);
    bool is_atom(unique_ptr<Expr>& result);
    bool is_band(unique_ptr<Expr>& result);
    bool is_bor(unique_ptr<Expr>& result);
    bool is_bxor(unique_ptr<Expr>& result);
    bool is_call_or_asg(unique_ptr<Stmt>& result);
    bool is_comparison(unique_ptr<Expr>& result);
    bool is_compound(unique_ptr<Stmt>& result);
    bool is_definition(unique_ptr<Stmt>& result);
    bool is_designator(unique_ptr<Expr>& result);
    bool is_expression(unique_ptr<Expr>& result);
    bool is_factor(unique_ptr<Expr>& result);
    bool is_field_col(vector<FieldDefPtr>& result);
    bool is_field_row(vector<FieldDefPtr>& result);
    bool is_field(FieldDefPtr& result);
    bool is_function(unique_ptr<Stmt>& result);
    bool is_if(unique_ptr<Stmt>& result);
    bool is_list(unique_ptr<Expr>& result);
    bool is_module(vector<unique_ptr<Stmt>>& stmts);
    bool is_not(unique_ptr<Expr>& result);
    bool is_or(unique_ptr<Expr>& result);
    bool is_parameter(ParamDefExprPtr& result);
    bool is_power(unique_ptr<Expr>& result);
    bool is_relation(BinaryOpKind& result, Context& context);
    bool is_return(unique_ptr<Stmt>& result);
    bool is_selector(unique_ptr<Expr>& result);
    bool is_shift(unique_ptr<Expr>& result);
    bool is_small(unique_ptr<Stmt>& result);
    bool is_stmt_col(vector<unique_ptr<Stmt>>& result);
    bool is_stmt_row(vector<unique_ptr<Stmt>>& result);
    bool is_structure(unique_ptr<Stmt>& result);
    bool is_suite(vector<unique_ptr<Stmt>>& result);
    bool is_term(unique_ptr<Expr>& result);
    bool is_type(unique_ptr<Expr>& result);
    bool is_while(unique_ptr<Stmt>& result);
};

} // namespace quirk