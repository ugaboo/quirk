#include "parser.h"
#include "../compilation_error.h"
#include <cassert>
#include <stdexcept>

namespace quirk {

Parser::Parser(std::string filename) : scanner(filename), filename(filename) {}

bool Parser::parse(std::unique_ptr<ast::TranslationUnit>& result)
{
    std::vector<std::unique_ptr<ast::Stmt>> stmts;
    std::unique_ptr<ast::Stmt> s;
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
    result = std::make_unique<ast::TranslationUnit>(filename, stmts);
    return true;
}

bool Parser::is_definition(std::unique_ptr<ast::Stmt>& result)
{
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

bool Parser::are_statements(std::vector<std::unique_ptr<ast::Stmt>>& result)
{
    std::unique_ptr<ast::Stmt> s;

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

bool Parser::is_compound(std::unique_ptr<ast::Stmt>& result)
{
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

bool Parser::is_stmt_row(std::vector<std::unique_ptr<ast::Stmt>>& result)
{
    std::unique_ptr<ast::Stmt> s;

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

bool Parser::is_stmt_col(std::vector<std::unique_ptr<ast::Stmt>>& result)
{
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

bool Parser::is_small(std::unique_ptr<ast::Stmt>& result)
{
    if (is_call_or_asg(result)) {
        goto END;
    }
    if (is_return(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::KwBreak) {
        result = std::make_unique<ast::BreakStmt>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwContinue) {
        result = std::make_unique<ast::ContinueStmt>(scanner.get_context());
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_call_or_asg(std::unique_ptr<ast::Stmt>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> desig, type, expr;

    if (is_designator(desig)) {
        auto func_call = dynamic_cast<ast::CallExpr*>(desig.get());
        if (func_call != nullptr) {
            desig.release();
            std::unique_ptr<ast::CallExpr> ptr(func_call);
            result = std::make_unique<ast::CallStmt>(ptr);
            return true;
        }
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Colon) {
        context = scanner.get_context();
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
        context = scanner.get_context();
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
    result = std::make_unique<ast::AsgStmt>(context, desig, type, expr);
    return true;
}

bool Parser::is_type(std::unique_ptr<ast::Expr>& result)
{
    if (scanner.get_token() == Token::Name) {
        result = std::make_unique<ast::NameLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_return(std::unique_ptr<ast::Stmt>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> expr;

    if (scanner.get_token() == Token::KwReturn) {
        context = scanner.get_context();
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
    result = std::make_unique<ast::ReturnStmt>(context, expr);
    return true;
}

bool Parser::are_expressions(std::vector<std::unique_ptr<ast::Expr>>& result)
{
    std::unique_ptr<ast::Expr> expr;

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

bool Parser::is_expression(std::unique_ptr<ast::Expr>& result)
{
    if (is_or(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_or(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> right;

    if (is_and(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_and(right)) {
        result = std::make_unique<ast::BinaryExpr>(context, ast::BinaryOpKind::Or, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::KwOr) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_and(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> right;

    if (is_not(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_not(right)) {
        result = std::make_unique<ast::BinaryExpr>(context, ast::BinaryOpKind::And, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::KwAnd) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_not(std::unique_ptr<ast::Expr>& result)
{
    Context context;

    if (scanner.get_token() == Token::KwNot) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (is_comparison(result)) {
        goto END;
    }
    return false;
L1:
    if (is_not(result)) {
        result = std::make_unique<ast::UnaryExpr>(context, ast::UnaryOpKind::Not, result);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_comparison(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    ast::BinaryOpKind kind;
    std::unique_ptr<ast::Expr> right;

    if (is_bor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_bor(right)) {
        result = std::make_unique<ast::BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (is_relation(kind, context)) {
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_relation(ast::BinaryOpKind& result, Context& context)
{
    if (scanner.get_token() == Token::Less) {
        result = ast::BinaryOpKind::Less;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Greater) {
        result = ast::BinaryOpKind::Greater;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Equal) {
        result = ast::BinaryOpKind::Equal;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::LessOrEqual) {
        result = ast::BinaryOpKind::LessOrEqual;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::GreaterOrEqual) {
        result = ast::BinaryOpKind::GreaterOrEqual;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::NotEqual) {
        result = ast::BinaryOpKind::NotEqual;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_bor(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> right;

    if (is_bxor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_bxor(right)) {
        result =
            std::make_unique<ast::BinaryExpr>(context, ast::BinaryOpKind::BitOr, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::BitOr) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_bxor(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> right;

    if (is_band(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_band(right)) {
        result =
            std::make_unique<ast::BinaryExpr>(context, ast::BinaryOpKind::BitXor, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::BitXor) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_band(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> right;

    if (is_shift(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_shift(right)) {
        result =
            std::make_unique<ast::BinaryExpr>(context, ast::BinaryOpKind::BitAnd, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::BitAnd) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_shift(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    ast::BinaryOpKind kind;
    std::unique_ptr<ast::Expr> right;

    if (is_arith(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_arith(right)) {
        result = std::make_unique<ast::BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::LeftShift) {
        kind = ast::BinaryOpKind::LeftShift;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::RightShift) {
        kind = ast::BinaryOpKind::RightShift;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_arith(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    ast::BinaryOpKind kind;
    std::unique_ptr<ast::Expr> right;

    if (is_term(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_term(right)) {
        result = std::make_unique<ast::BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Plus) {
        kind = ast::BinaryOpKind::Add;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Minus) {
        kind = ast::BinaryOpKind::Sub;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_term(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    ast::BinaryOpKind kind;
    std::unique_ptr<ast::Expr> right;

    if (is_factor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_factor(right)) {
        result = std::make_unique<ast::BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Star) {
        kind = ast::BinaryOpKind::Mul;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Slash) {
        kind = ast::BinaryOpKind::Div;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Percent) {
        kind = ast::BinaryOpKind::Mod;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::DoubleSlash) {
        kind = ast::BinaryOpKind::IntDiv;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_factor(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    ast::UnaryOpKind kind;

    if (is_power(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::Plus) {
        kind = ast::UnaryOpKind::Plus;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Minus) {
        kind = ast::UnaryOpKind::Minus;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::BitNot) {
        kind = ast::UnaryOpKind::BitNot;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_factor(result)) {
        result = std::make_unique<ast::UnaryExpr>(context, kind, result);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_power(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> exp;

    if (is_designator(result)) {
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Power) {
        context = scanner.get_context();
        scanner.move();
        goto L2;
    }
    goto END;
L2:
    if (is_factor(exp)) {
        result = std::make_unique<ast::BinaryExpr>(context, ast::BinaryOpKind::Power, result, exp);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_designator(std::unique_ptr<ast::Expr>& result)
{
    if (is_atom(result)) {
        goto L1;
    }
    return false;
L1:
    if (is_selector(result)) { // atom's result is passed into the selector check
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_atom(std::unique_ptr<ast::Expr>& result)
{
    if (is_list(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::Name) {
        result = std::make_unique<ast::NameLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Int) {
        result = std::make_unique<ast::IntLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Float) {
        result = std::make_unique<ast::FloatLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwTrue) {
        result = std::make_unique<ast::BoolLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwFalse) {
        result = std::make_unique<ast::BoolLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwNone) {
        result = std::make_unique<ast::NoneLiteral>(scanner.get_context());
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

bool Parser::is_selector(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::vector<std::unique_ptr<ast::Expr>> args, keys;

    if (scanner.get_token() == Token::LeftParenthesis) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::LeftBracket) {
        context = scanner.get_context();
        scanner.move();
        goto L3;
    }
    if (scanner.get_token() == Token::Point) {
        context = scanner.get_context();
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
        result = std::make_unique<ast::CallExpr>(context, result, args);
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
        result = std::make_unique<ast::SubscriptExpr>(context, result, keys);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
L5:
    if (scanner.get_token() == Token::Name) {
        auto name = std::make_unique<ast::NameLiteral>(scanner.get_context());
        result = std::make_unique<ast::MemberAccessExpr>(context, result, name);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_list(std::unique_ptr<ast::Expr>& result)
{
    Context context;
    std::vector<std::unique_ptr<ast::Expr>> exprs;

    if (scanner.get_token() == Token::LeftBracket) {
        context = scanner.get_context();
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
    result = std::make_unique<ast::ListLiteral>(context, exprs);
    return true;
}

bool Parser::is_function(std::unique_ptr<ast::Stmt>& result)
{
    Context context;
    std::unique_ptr<ast::NameLiteral> name;
    std::vector<std::unique_ptr<ast::ParamDefExpr>> params;
    std::unique_ptr<ast::Expr> ret_type_expr;
    std::vector<std::unique_ptr<ast::Stmt>> stmts;

    if (scanner.get_token() == Token::KwDef) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Name) {
        name = std::make_unique<ast::NameLiteral>(scanner.get_context());
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
    result = std::make_unique<ast::FuncDefStmt>(context, name, params, ret_type_expr, stmts);
    return true;
}

bool Parser::are_parameters(std::vector<std::unique_ptr<ast::ParamDefExpr>>& result)
{
    std::unique_ptr<ast::ParamDefExpr> param;

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

bool Parser::is_parameter(std::unique_ptr<ast::ParamDefExpr>& result)
{
    std::unique_ptr<ast::NameLiteral> name;
    std::unique_ptr<ast::Expr> type;

    if (scanner.get_token() == Token::Name) {
        name = std::make_unique<ast::NameLiteral>(scanner.get_context());
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
    result = std::make_unique<ast::ParamDefExpr>(name, type);
    return true;
}

bool Parser::is_if(std::unique_ptr<ast::Stmt>& result)
{
    Context context;
    std::vector<std::unique_ptr<ast::IfStmt::Branch>> branches;
    std::vector<std::unique_ptr<ast::Stmt>> else_stmts;

    std::unique_ptr<ast::Expr> condition;
    std::vector<std::unique_ptr<ast::Stmt>> stmts;

    if (scanner.get_token() == Token::KwIf) {
        context = scanner.get_context();
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
    stmts.clear();
    if (is_suite(stmts)) {
        branches.push_back(std::make_unique<ast::IfStmt::Branch>(condition, stmts));
        goto L4;
    }
    throw CompilationError::InvalidSyntax;
L4:
    if (scanner.get_token() == Token::KwElif) {
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
    result = std::make_unique<ast::IfStmt>(context, branches, else_stmts);
    return true;
}

bool Parser::is_while(std::unique_ptr<ast::Stmt>& result)
{
    Context context;
    std::unique_ptr<ast::Expr> condition;
    std::vector<std::unique_ptr<ast::Stmt>> body;

    if (scanner.get_token() == Token::KwWhile) {
        context = scanner.get_context();
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
    result = std::make_unique<ast::WhileStmt>(context, condition, body);
    return true;
}

bool Parser::is_suite(std::vector<std::unique_ptr<ast::Stmt>>& result)
{
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

bool Parser::is_structure(std::unique_ptr<ast::Stmt>& result)
{
    Context context;
    std::unique_ptr<ast::NameLiteral> name;
    std::vector<std::unique_ptr<ast::FieldDefStmt>> fields;

    if (scanner.get_token() == Token::KwStruct) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Name) {
        name = std::make_unique<ast::NameLiteral>(scanner.get_context());
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
    result = std::make_unique<ast::StructDefStmt>(context, name, fields);
    return true;
}

bool Parser::are_fields(std::vector<std::unique_ptr<ast::FieldDefStmt>>& result)
{
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

bool Parser::is_field_row(std::vector<std::unique_ptr<ast::FieldDefStmt>>& result)
{
    std::unique_ptr<ast::FieldDefStmt> field;

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

bool Parser::is_field_col(std::vector<std::unique_ptr<ast::FieldDefStmt>>& result)
{
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

bool Parser::is_field(std::unique_ptr<ast::FieldDefStmt>& result)
{
    std::unique_ptr<ast::NameLiteral> name;
    std::unique_ptr<ast::Expr> type;
    std::unique_ptr<ast::Expr> init_expr;

    if (scanner.get_token() == Token::Name) {
        name = std::make_unique<ast::NameLiteral>(scanner.get_context());
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
    result = std::make_unique<ast::FieldDefStmt>(name, type, init_expr);
    return true;
}

} // namespace quirk