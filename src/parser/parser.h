#pragma once

#include <memory>
#include <vector>

#include "../ast/visitor.h"
#include "../scanner/scanner.h"

namespace quirk {

class Parser {
    Scanner scanner;

public:
    Parser(std::string filename);

    bool parse(std::unique_ptr<ast::TranslationUnit>& result);

private:
    bool are_expressions(std::vector<std::unique_ptr<ast::Expr>>& result);
    bool are_fields(std::vector<std::unique_ptr<ast::FieldDefStmt>>& result);
    bool are_parameters(std::vector<std::unique_ptr<ast::ParamDefExpr>>& result);
    bool are_statements(std::vector<std::unique_ptr<ast::Stmt>>& result);
    bool is_and(std::unique_ptr<ast::Expr>& result);
    bool is_arith(std::unique_ptr<ast::Expr>& result);
    bool is_atom(std::unique_ptr<ast::Expr>& result);
    bool is_band(std::unique_ptr<ast::Expr>& result);
    bool is_bor(std::unique_ptr<ast::Expr>& result);
    bool is_bxor(std::unique_ptr<ast::Expr>& result);
    bool is_call_or_asg(std::unique_ptr<ast::Stmt>& result);
    bool is_comparison(std::unique_ptr<ast::Expr>& result);
    bool is_compound(std::unique_ptr<ast::Stmt>& result);
    bool is_definition(std::unique_ptr<ast::Stmt>& result);
    bool is_designator(std::unique_ptr<ast::Expr>& result);
    bool is_expression(std::unique_ptr<ast::Expr>& result);
    bool is_factor(std::unique_ptr<ast::Expr>& result);
    bool is_field_col(std::vector<std::unique_ptr<ast::FieldDefStmt>>& result);
    bool is_field_row(std::vector<std::unique_ptr<ast::FieldDefStmt>>& result);
    bool is_field(std::unique_ptr<ast::FieldDefStmt>& result);
    bool is_function(std::unique_ptr<ast::Stmt>& result);
    bool is_if(std::unique_ptr<ast::Stmt>& result);
    bool is_list(std::unique_ptr<ast::Expr>& result);
    bool is_module(std::vector<std::unique_ptr<ast::Stmt>>& stmts);
    bool is_not(std::unique_ptr<ast::Expr>& result);
    bool is_or(std::unique_ptr<ast::Expr>& result);
    bool is_parameter(std::unique_ptr<ast::ParamDefExpr>& result);
    bool is_power(std::unique_ptr<ast::Expr>& result);
    bool is_relation(ast::BinaryOpKind& result, Context& context);
    bool is_return(std::unique_ptr<ast::Stmt>& result);
    bool is_selector(std::unique_ptr<ast::Expr>& result);
    bool is_shift(std::unique_ptr<ast::Expr>& result);
    bool is_small(std::unique_ptr<ast::Stmt>& result);
    bool is_stmt_col(std::vector<std::unique_ptr<ast::Stmt>>& result);
    bool is_stmt_row(std::vector<std::unique_ptr<ast::Stmt>>& result);
    bool is_structure(std::unique_ptr<ast::Stmt>& result);
    bool is_suite(std::vector<std::unique_ptr<ast::Stmt>>& result);
    bool is_term(std::unique_ptr<ast::Expr>& result);
    bool is_type(std::unique_ptr<ast::Expr>& result);
    bool is_while(std::unique_ptr<ast::Stmt>& result);
};

} // namespace quirk