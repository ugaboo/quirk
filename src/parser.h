#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "ast/visitor.h"
#include "scanner.h"

namespace quirk {

using std::unique_ptr;
using std::vector;

class Parser {
    Scanner scanner;

public:
    Parser(string filename);

    bool parse(unique_ptr<ast::Module>& result);

private:
    ast::Context get_context();

    bool are_expressions(vector<unique_ptr<ast::Expr>>& result);
    bool are_fields(vector<unique_ptr<ast::FieldDef>>& result);
    bool are_parameters(vector<unique_ptr<ast::ParameterDef>>& result);
    bool are_statements(vector<unique_ptr<ast::Stmt>>& result);
    bool is_and(unique_ptr<ast::Expr>& result);
    bool is_arith(unique_ptr<ast::Expr>& result);
    bool is_atom(unique_ptr<ast::Expr>& result);
    bool is_band(unique_ptr<ast::Expr>& result);
    bool is_bor(unique_ptr<ast::Expr>& result);
    bool is_bxor(unique_ptr<ast::Expr>& result);
    bool is_call_or_asg(unique_ptr<ast::Stmt>& result);
    bool is_comparison(unique_ptr<ast::Expr>& result);
    bool is_compound(unique_ptr<ast::Stmt>& result);
    bool is_definition(unique_ptr<ast::Stmt>& result);
    bool is_designator(unique_ptr<ast::Expr>& result);
    bool is_expression(unique_ptr<ast::Expr>& result);
    bool is_factor(unique_ptr<ast::Expr>& result);
    bool is_field_col(vector<unique_ptr<ast::FieldDef>>& result);
    bool is_field_row(vector<unique_ptr<ast::FieldDef>>& result);
    bool is_field(unique_ptr<ast::FieldDef>& result);
    bool is_function(unique_ptr<ast::Stmt>& result);
    bool is_if(unique_ptr<ast::Stmt>& result);
    bool is_list(unique_ptr<ast::Expr>& result);
    bool is_module(unique_ptr<ast::Module>& result);
    bool is_not(unique_ptr<ast::Expr>& result);
    bool is_or(unique_ptr<ast::Expr>& result);
    bool is_parameter(unique_ptr<ast::ParameterDef>& result);
    bool is_power(unique_ptr<ast::Expr>& result);
    bool is_relation(ast::BinaryExpr::Kind& result);
    bool is_return(unique_ptr<ast::Stmt>& result);
    bool is_selector(unique_ptr<ast::Expr>& result);
    bool is_shift(unique_ptr<ast::Expr>& result);
    bool is_small(unique_ptr<ast::Stmt>& result);
    bool is_stmt_col(vector<unique_ptr<ast::Stmt>>& result);
    bool is_stmt_row(vector<unique_ptr<ast::Stmt>>& result);
    bool is_structure(unique_ptr<ast::Stmt>& result);
    bool is_suite(vector<unique_ptr<ast::Stmt>>& result);
    bool is_term(unique_ptr<ast::Expr>& result);
    bool is_type(unique_ptr<ast::Expr>& result);
    bool is_while(unique_ptr<ast::Stmt>& result);
};

}  // namespace quirk