#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "scanner/scanner.h"
#include "ast/headers.h"

namespace quirk {

using std::unique_ptr;
using std::vector;

using namespace ast;

class Parser {
    Scanner scanner;

public:
    Parser(string filename);

    bool parse(vector<StmtPtr>& stmts);

private:
    bool are_expressions(vector<ExprPtr>& result);
    bool are_fields(vector<FieldDefPtr>& result);
    bool are_parameters(vector<ParamDefExprPtr>& result);
    bool are_statements(vector<StmtPtr>& result);
    bool is_and(ExprPtr& result);
    bool is_arith(ExprPtr& result);
    bool is_atom(ExprPtr& result);
    bool is_band(ExprPtr& result);
    bool is_bor(ExprPtr& result);
    bool is_bxor(ExprPtr& result);
    bool is_call_or_asg(StmtPtr& result);
    bool is_comparison(ExprPtr& result);
    bool is_compound(StmtPtr& result);
    bool is_definition(StmtPtr& result);
    bool is_designator(ExprPtr& result);
    bool is_expression(ExprPtr& result);
    bool is_factor(ExprPtr& result);
    bool is_field_col(vector<FieldDefPtr>& result);
    bool is_field_row(vector<FieldDefPtr>& result);
    bool is_field(FieldDefPtr& result);
    bool is_function(StmtPtr& result);
    bool is_if(StmtPtr& result);
    bool is_list(ExprPtr& result);
    bool is_module(vector<StmtPtr>& stmts);
    bool is_not(ExprPtr& result);
    bool is_or(ExprPtr& result);
    bool is_parameter(ParamDefExprPtr& result);
    bool is_power(ExprPtr& result);
    bool is_relation(BinaryOpKind& result, Context& context);
    bool is_return(StmtPtr& result);
    bool is_selector(ExprPtr& result);
    bool is_shift(ExprPtr& result);
    bool is_small(StmtPtr& result);
    bool is_stmt_col(vector<StmtPtr>& result);
    bool is_stmt_row(vector<StmtPtr>& result);
    bool is_structure(StmtPtr& result);
    bool is_suite(vector<StmtPtr>& result);
    bool is_term(ExprPtr& result);
    bool is_type(ExprPtr& result);
    bool is_while(StmtPtr& result);
};

}  // namespace quirk