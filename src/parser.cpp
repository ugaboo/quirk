#include "parser.h"
#include <cassert>
#include <stdexcept>
#include "compilation_error.h"

using std::make_unique;

namespace quirk {

Parser::Parser(string filename) : scanner(filename) {}

bool Parser::parse(unique_ptr<ast::Module>& result) {
    return is_module(result);
}

ast::Context Parser::get_context() {
    return ast::Context{.line = scanner.get_line(), .column = scanner.get_column(), .value = scanner.get_value()};
}

bool Parser::is_module(unique_ptr<ast::Module>& result) {
    unique_ptr<ast::Stmt> s;
    vector<unique_ptr<ast::Stmt>> stmts;
L0:
    if (are_statements(stmts)) {
        goto L0;
    }
    if (is_definition(s)) {
        stmts.push_back(move(s));
        goto L0;
    }
    if (scanner.get_token() == Token::EndMarker) {
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::Module>(stmts);
    return true;
}

bool Parser::is_definition(unique_ptr<ast::Stmt>& result) {
    if (is_function(result)) {
        goto END;
    }
    if (is_structure(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::are_statements(vector<unique_ptr<ast::Stmt>>& result) {
    unique_ptr<ast::Stmt> s;

    if (is_stmt_row(result)) {
        goto END;
    }
    if (is_compound(s)) {
        result.push_back(move(s));
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_compound(unique_ptr<ast::Stmt>& result) {
    if (is_if(result)) {
        goto END;
    }
    if (is_while(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_stmt_row(vector<unique_ptr<ast::Stmt>>& result) {
    unique_ptr<ast::Stmt> s;

    if (is_small(s)) {
        result.push_back(move(s));
        goto L2;
    }
    if (scanner.get_token() == Token::KwPass) {
        scanner.move();
        goto L2;
    }
    return false;
L1:
    if (is_small(s)) {
        result.push_back(move(s));
        goto L2;
    }
    if (scanner.get_token() == Token::KwPass) {
        scanner.move();
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Semicolon) {
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::NewLine) {
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_stmt_col(vector<unique_ptr<ast::Stmt>>& result) {
    if (scanner.get_token() == Token::NewLine) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Indent) {
        scanner.move();
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (are_statements(result)) {
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (scanner.get_token() == Token::Dedent) {
        scanner.move();
        goto END;
    }
    goto L2;
END:
    return true;
}

bool Parser::is_small(unique_ptr<ast::Stmt>& result) {
    if (is_call_or_asg(result)) {
        goto END;
    }
    if (is_return(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::KwBreak) {
        result = make_unique<ast::BreakStmt>();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwContinue) {
        result = make_unique<ast::ContinueStmt>();
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_call_or_asg(unique_ptr<ast::Stmt>& result) {
    unique_ptr<ast::Expr> desig, type, expr;

    if (is_designator(desig)) {
        auto func_call = dynamic_cast<ast::CallExprStmt*>(desig.get());
        if (func_call != nullptr) {
            desig.release();
            result.reset(func_call);
            return true;
        }
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L2;
    }
    goto L3;
L2:
    if (is_type(type)) {
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (scanner.get_token() == Token::AsgStmt) {
        scanner.move();
        goto L4;
    }
    goto END;
L4:
    if (is_expression(expr)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    if (type == nullptr && expr == nullptr) {
        throw CompilationError::InvalidSyntax;
    }
    result = make_unique<ast::AsgStmt>(desig, type, expr);
    return true;
}

bool Parser::is_type(unique_ptr<ast::Expr>& result) {
    if (scanner.get_token() == Token::Name) {
        result = make_unique<ast::NameLiteral>(get_context());
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_return(unique_ptr<ast::Stmt>& result) {
    unique_ptr<ast::Expr> expr;

    if (scanner.get_token() == Token::KwReturn) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_expression(expr)) {
        goto END;
    }
    goto END;
END:
    result = make_unique<ast::ReturnStmt>(expr);
    return true;
}

bool Parser::are_expressions(vector<unique_ptr<ast::Expr>>& result) {
    unique_ptr<ast::Expr> expr;

    if (is_expression(expr)) {
        result.push_back(move(expr));
        goto L2;
    }
    return false;
L1:
    if (is_expression(expr)) {
        result.push_back(move(expr));
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Comma) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_expression(unique_ptr<ast::Expr>& result) {
    if (is_or(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_or(unique_ptr<ast::Expr>& result) {
    unique_ptr<ast::Expr> right;

    if (is_and(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_and(right)) {
        result = make_unique<ast::BinaryExpr>(ast::BinaryExpr::Kind::Or, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::KwOr) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_and(unique_ptr<ast::Expr>& result) {
    unique_ptr<ast::Expr> right;

    if (is_not(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_not(right)) {
        result = make_unique<ast::BinaryExpr>(ast::BinaryExpr::Kind::And, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::KwAnd) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_not(unique_ptr<ast::Expr>& result) {
    if (scanner.get_token() == Token::KwNot) {
        scanner.move();
        goto L1;
    }
    if (is_comparison(result)) {
        goto END;
    }
    return false;
L1:
    if (is_not(result)) {
        result = make_unique<ast::UnaryExpr>(ast::UnaryExpr::Kind::Not, result);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_comparison(unique_ptr<ast::Expr>& result) {
    ast::BinaryExpr::Kind kind;
    unique_ptr<ast::Expr> right;

    if (is_bor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_bor(right)) {
        result = make_unique<ast::BinaryExpr>(kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (is_relation(kind)) {
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_relation(ast::BinaryExpr::Kind& result) {
    if (scanner.get_token() == Token::Less) {
        result = ast::BinaryExpr::Kind::Less;
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Greater) {
        result = ast::BinaryExpr::Kind::Greater;
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Equal) {
        result = ast::BinaryExpr::Kind::Equal;
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::LessOrEqual) {
        result = ast::BinaryExpr::Kind::LessOrEqual;
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::GreaterOrEqual) {
        result = ast::BinaryExpr::Kind::GreaterOrEqual;
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::NotEqual) {
        result = ast::BinaryExpr::Kind::NotEqual;
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_bor(unique_ptr<ast::Expr>& result) {
    unique_ptr<ast::Expr> right;

    if (is_bxor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_bxor(right)) {
        result = make_unique<ast::BinaryExpr>(ast::BinaryExpr::Kind::BitOr, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::BitOr) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_bxor(unique_ptr<ast::Expr>& result) {
    unique_ptr<ast::Expr> right;

    if (is_band(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_band(right)) {
        result = make_unique<ast::BinaryExpr>(ast::BinaryExpr::Kind::BitXor, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::BitXor) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_band(unique_ptr<ast::Expr>& result) {
    unique_ptr<ast::Expr> right;

    if (is_shift(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_shift(right)) {
        result = make_unique<ast::BinaryExpr>(ast::BinaryExpr::Kind::BitAnd, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::BitAnd) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_shift(unique_ptr<ast::Expr>& result) {
    ast::BinaryExpr::Kind kind;
    unique_ptr<ast::Expr> right;

    if (is_arith(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_arith(right)) {
        result = make_unique<ast::BinaryExpr>(kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::LeftShift) {
        kind = ast::BinaryExpr::Kind::LeftShift;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::RightShift) {
        kind = ast::BinaryExpr::Kind::RightShift;
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_arith(unique_ptr<ast::Expr>& result) {
    ast::BinaryExpr::Kind kind;
    unique_ptr<ast::Expr> right;

    if (is_term(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_term(right)) {
        result = make_unique<ast::BinaryExpr>(kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Plus) {
        kind = ast::BinaryExpr::Kind::Add;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Minus) {
        kind = ast::BinaryExpr::Kind::Sub;
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_term(unique_ptr<ast::Expr>& result) {
    ast::BinaryExpr::Kind kind;
    unique_ptr<ast::Expr> right;

    if (is_factor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_factor(right)) {
        result = make_unique<ast::BinaryExpr>(kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Star) {
        kind = ast::BinaryExpr::Kind::Mul;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Slash) {
        kind = ast::BinaryExpr::Kind::Div;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Percent) {
        kind = ast::BinaryExpr::Kind::Mod;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::DoubleSlash) {
        kind = ast::BinaryExpr::Kind::IntDiv;
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_factor(unique_ptr<ast::Expr>& result) {
    ast::UnaryExpr::Kind kind;

    if (is_power(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::Plus) {
        kind = ast::UnaryExpr::Kind::Plus;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Minus) {
        kind = ast::UnaryExpr::Kind::Minus;
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::BitNot) {
        kind = ast::UnaryExpr::Kind::BitNot;
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_factor(result)) {
        result = make_unique<ast::UnaryExpr>(kind, result);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_power(unique_ptr<ast::Expr>& result) {
    unique_ptr<ast::Expr> exp;

    if (is_designator(result)) {
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Power) {
        scanner.move();
        goto L2;
    }
    goto END;
L2:
    if (is_factor(exp)) {
        result = make_unique<ast::BinaryExpr>(ast::BinaryExpr::Kind::Power, result, exp);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_designator(unique_ptr<ast::Expr>& result) {
    if (is_atom(result)) {
        goto L1;
    }
    return false;
L1:
    if (is_selector(result)) {  // atom's result is passed into the selector check
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_atom(unique_ptr<ast::Expr>& result) {
    if (is_list(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::Name) {
        result = make_unique<ast::NameLiteral>(get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Int) {
        result = make_unique<ast::IntLiteral>(get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Float) {
        result = make_unique<ast::FloatLiteral>(get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwTrue) {
        result = make_unique<ast::BoolLiteral>(get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwFalse) {
        result = make_unique<ast::BoolLiteral>(get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwNone) {
        result = make_unique<ast::NoneLiteral>(get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::LeftParenthesis) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_expression(result)) {
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::RightParenthesis) {
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_selector(unique_ptr<ast::Expr>& result) {
    vector<unique_ptr<ast::Expr>> args, keys;

    if (scanner.get_token() == Token::LeftParenthesis) {
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::LeftBracket) {
        scanner.move();
        goto L3;
    }
    if (scanner.get_token() == Token::Point) {
        scanner.move();
        goto L5;
    }
    return false;
L1:
    if (are_expressions(args)) {
        goto L2;
    }
    goto L2;
L2:
    if (scanner.get_token() == Token::RightParenthesis) {
        result = make_unique<ast::CallExprStmt>(result, args);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (are_expressions(keys)) {
        goto L4;
    }
    throw CompilationError::InvalidSyntax;
L4:
    if (scanner.get_token() == Token::RightBracket) {
        result = make_unique<ast::SubscriptExpr>(result, keys);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
L5:
    if (scanner.get_token() == Token::Name) {
        auto name = make_unique<ast::NameLiteral>(get_context());
        result = make_unique<ast::MemberAccessExpr>(result, name);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_list(unique_ptr<ast::Expr>& result) {
    vector<unique_ptr<ast::Expr>> exprs;

    if (scanner.get_token() == Token::LeftBracket) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (are_expressions(exprs)) {
        goto L2;
    }
    goto L2;
L2:
    if (scanner.get_token() == Token::RightBracket) {
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::ListLiteral>(exprs);
    return true;
}

bool Parser::is_function(unique_ptr<ast::Stmt>& result) {
    ast::Context context;
    vector<unique_ptr<ast::ParameterDef>> params;
    unique_ptr<ast::Expr> ret_type_expr;
    vector<unique_ptr<ast::Stmt>> stmts;

    if (scanner.get_token() == Token::KwDef) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Name) {
        context = get_context();
        scanner.move();
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::LeftParenthesis) {
        scanner.move();
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (are_parameters(params)) {
        goto L4;
    }
    goto L4;
L4:
    if (scanner.get_token() == Token::RightParenthesis) {
        scanner.move();
        goto L5;
    }
    throw CompilationError::InvalidSyntax;
L5:
    if (scanner.get_token() == Token::RightArrow) {
        scanner.move();
        goto L6;
    }
    goto L7;
L6:
    if (is_type(ret_type_expr)) {
        goto L7;
    }
    throw CompilationError::InvalidSyntax;
L7:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L8;
    }
    throw CompilationError::InvalidSyntax;
L8:
    if (is_suite(stmts)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::FuncDefStmt>(context, params, ret_type_expr, stmts);
    return true;
}

bool Parser::are_parameters(vector<unique_ptr<ast::ParameterDef>>& result) {
    unique_ptr<ast::ParameterDef> param;

    if (is_parameter(param)) {
        result.push_back(move(param));
        goto L2;
    }
    return false;
L1:
    if (is_parameter(param)) {
        result.push_back(move(param));
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Comma) {
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_parameter(unique_ptr<ast::ParameterDef>& result) {
    ast::Context context;
    unique_ptr<ast::Expr> type;

    if (scanner.get_token() == Token::Name) {
        context = get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L2;
    }
    goto END;
L2:
    if (is_type(type)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::ParameterDef>(context, type);
    return true;
}

bool Parser::is_if(unique_ptr<ast::Stmt>& result) {
    using Condition = unique_ptr<ast::Expr>;
    using Statements = vector<unique_ptr<ast::Stmt>>;
    using Branch = std::pair<Condition, Statements>;

    vector<Branch> branches;
    Statements else_stmts;

    if (scanner.get_token() == Token::KwIf) {
        branches.emplace_back();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_expression(branches.back().first)) {
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (is_suite(branches.back().second)) {
        goto L4;
    }
    throw CompilationError::InvalidSyntax;
L4:
    if (scanner.get_token() == Token::KwElif) {
        branches.emplace_back();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::KwElse) {
        scanner.move();
        goto L5;
    }
    goto END;
L5:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L6;
    }
    throw CompilationError::InvalidSyntax;
L6:
    if (is_suite(else_stmts)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::IfStmt>(branches, else_stmts);
    return true;
}

bool Parser::is_while(unique_ptr<ast::Stmt>& result) {
    unique_ptr<ast::Expr> condition;
    vector<unique_ptr<ast::Stmt>> body;

    if (scanner.get_token() == Token::KwWhile) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_expression(condition)) {
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (is_suite(body)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::WhileStmt>(condition, body);
    return true;
}

bool Parser::is_suite(vector<unique_ptr<ast::Stmt>>& result) {
    if (is_stmt_row(result)) {
        goto END;
    }
    if (is_stmt_col(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_structure(unique_ptr<ast::Stmt>& result) {
    ast::Context context;
    vector<unique_ptr<ast::FieldDef>> fields;

    if (scanner.get_token() == Token::KwStruct) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Name) {
        context = get_context();
        scanner.move();
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (are_fields(fields)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::StructDefStmt>(context, fields);
    return true;
}

bool Parser::are_fields(vector<unique_ptr<ast::FieldDef>>& result) {
    if (is_field_row(result)) {
        goto END;
    }
    if (is_field_col(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_field_row(vector<unique_ptr<ast::FieldDef>>& result) {
    unique_ptr<ast::FieldDef> field;

    if (is_field(field)) {
        result.push_back(move(field));
        goto L2;
    }
    if (scanner.get_token() == Token::KwPass) {
        scanner.move();
        goto L2;
    }
    return false;
L1:
    if (is_field(field)) {
        result.push_back(move(field));
        goto L2;
    }
    if (scanner.get_token() == Token::KwPass) {
        scanner.move();
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Semicolon) {
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::NewLine) {
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_field_col(vector<unique_ptr<ast::FieldDef>>& result) {
    if (scanner.get_token() == Token::NewLine) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Indent) {
        scanner.move();
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (is_field_row(result)) {
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (scanner.get_token() == Token::Dedent) {
        scanner.move();
        goto END;
    }
    goto L2;
END:
    return true;
}

bool Parser::is_field(unique_ptr<ast::FieldDef>& result) {
    ast::Context context;
    unique_ptr<ast::Expr> type;
    unique_ptr<ast::Expr> init_expr;

    if (scanner.get_token() == Token::Name) {
        context = get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Colon) {
        scanner.move();
        goto L2;
    }
    goto L3;
L2:
    if (is_type(type)) {
        goto L3;
    }
    throw CompilationError::InvalidSyntax;
L3:
    if (scanner.get_token() == Token::AsgStmt) {
        scanner.move();
        goto L4;
    }
    goto END;
L4:
    if (is_expression(init_expr)) {
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    result = make_unique<ast::FieldDef>(context, type, init_expr);
    return true;
}

}  // namespace quirk