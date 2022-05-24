#include "parser.h"
#include <cassert>
#include <stdexcept>
#include "compilation_error.h"

using std::make_unique;

namespace quirk {

using namespace ast;

Parser::Parser(string filename) : scanner(filename) {}

bool Parser::parse(vector<StmtPtr>& result) {
    return is_module(result);
}

bool Parser::is_module(vector<StmtPtr>& result) {
    StmtPtr s;
L0:
    if (are_statements(result)) {
        goto L0;
    }
    if (is_definition(s)) {
        result.push_back(move(s));
        goto L0;
    }
    if (scanner.get_token() == Token::EndMarker) {
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_definition(StmtPtr& result) {
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

bool Parser::are_statements(vector<StmtPtr>& result) {
    StmtPtr s;

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

bool Parser::is_compound(StmtPtr& result) {
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

bool Parser::is_stmt_row(vector<StmtPtr>& result) {
    StmtPtr s;

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

bool Parser::is_stmt_col(vector<StmtPtr>& result) {
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

bool Parser::is_small(StmtPtr& result) {
    if (is_call_or_asg(result)) {
        goto END;
    }
    if (is_return(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::KwBreak) {
        result = make_unique<BreakStmt>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwContinue) {
        result = make_unique<ContinueStmt>(scanner.get_context());
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_call_or_asg(StmtPtr& result) {
    Context context;
    ExprPtr desig, type, expr;

    if (is_designator(desig)) {
        auto func_call = dynamic_cast<CallExpr*>(desig.get());
        if (func_call != nullptr) {
            desig.release();
            unique_ptr<CallExpr> ptr(func_call);
            result = make_unique<CallStmt>(ptr);
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
    result = make_unique<AsgStmt>(context, desig, type, expr);
    return true;
}

bool Parser::is_type(ExprPtr& result) {
    if (scanner.get_token() == Token::Name) {
        result = make_unique<NameLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_return(StmtPtr& result) {
    Context context;
    ExprPtr expr;

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
    result = make_unique<ReturnStmt>(context, expr);
    return true;
}

bool Parser::are_expressions(vector<ExprPtr>& result) {
    ExprPtr expr;

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

bool Parser::is_expression(ExprPtr& result) {
    if (is_or(result)) {
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_or(ExprPtr& result) {
    Context context;
    ExprPtr right;

    if (is_and(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_and(right)) {
        result = make_unique<BinaryExpr>(context, BinaryOpKind::Or, result, right);
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

bool Parser::is_and(ExprPtr& result) {
    Context context;
    ExprPtr right;

    if (is_not(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_not(right)) {
        result = make_unique<BinaryExpr>(context, BinaryOpKind::And, result, right);
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

bool Parser::is_not(ExprPtr& result) {
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
        result = make_unique<UnaryExpr>(context, UnaryOpKind::Not, result);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_comparison(ExprPtr& result) {
    Context      context;
    BinaryOpKind kind;
    ExprPtr      right;

    if (is_bor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_bor(right)) {
        result = make_unique<BinaryExpr>(context, kind, result, right);
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

bool Parser::is_relation(BinaryOpKind& result, Context& context) {
    if (scanner.get_token() == Token::Less) {
        result = BinaryOpKind::Less;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Greater) {
        result = BinaryOpKind::Greater;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Equal) {
        result = BinaryOpKind::Equal;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::LessOrEqual) {
        result = BinaryOpKind::LessOrEqual;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::GreaterOrEqual) {
        result = BinaryOpKind::GreaterOrEqual;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::NotEqual) {
        result = BinaryOpKind::NotEqual;
        context = scanner.get_context();
        scanner.move();
        goto END;
    }
    return false;
END:
    return true;
}

bool Parser::is_bor(ExprPtr& result) {
    Context context;
    ExprPtr right;

    if (is_bxor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_bxor(right)) {
        result = make_unique<BinaryExpr>(context, BinaryOpKind::BitOr, result, right);
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

bool Parser::is_bxor(ExprPtr& result) {
    Context context;
    ExprPtr right;

    if (is_band(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_band(right)) {
        result = make_unique<BinaryExpr>(context, BinaryOpKind::BitXor, result, right);
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

bool Parser::is_band(ExprPtr& result) {
    Context context;
    ExprPtr right;

    if (is_shift(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_shift(right)) {
        result = make_unique<BinaryExpr>(context, BinaryOpKind::BitAnd, result, right);
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

bool Parser::is_shift(ExprPtr& result) {
    Context      context;
    BinaryOpKind kind;
    ExprPtr      right;

    if (is_arith(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_arith(right)) {
        result = make_unique<BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::LeftShift) {
        kind = BinaryOpKind::LeftShift;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::RightShift) {
        kind = BinaryOpKind::RightShift;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_arith(ExprPtr& result) {
    Context      context;
    BinaryOpKind kind;
    ExprPtr      right;

    if (is_term(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_term(right)) {
        result = make_unique<BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Plus) {
        kind = BinaryOpKind::Add;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Minus) {
        kind = BinaryOpKind::Sub;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_term(ExprPtr& result) {
    Context      context;
    BinaryOpKind kind;
    ExprPtr      right;

    if (is_factor(result)) {
        goto L2;
    }
    return false;
L1:
    if (is_factor(right)) {
        result = make_unique<BinaryExpr>(context, kind, result, right);
        goto L2;
    }
    throw CompilationError::InvalidSyntax;
L2:
    if (scanner.get_token() == Token::Star) {
        kind = BinaryOpKind::Mul;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Slash) {
        kind = BinaryOpKind::Div;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Percent) {
        kind = BinaryOpKind::Mod;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::DoubleSlash) {
        kind = BinaryOpKind::IntDiv;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    goto END;
END:
    return true;
}

bool Parser::is_factor(ExprPtr& result) {
    Context     context;
    UnaryOpKind kind;

    if (is_power(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::Plus) {
        kind = UnaryOpKind::Plus;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::Minus) {
        kind = UnaryOpKind::Minus;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    if (scanner.get_token() == Token::BitNot) {
        kind = UnaryOpKind::BitNot;
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (is_factor(result)) {
        result = make_unique<UnaryExpr>(context, kind, result);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_power(ExprPtr& result) {
    Context context;
    ExprPtr exp;

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
        result = make_unique<BinaryExpr>(context, BinaryOpKind::Power, result, exp);
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_designator(ExprPtr& result) {
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

bool Parser::is_atom(ExprPtr& result) {
    if (is_list(result)) {
        goto END;
    }
    if (scanner.get_token() == Token::Name) {
        result = make_unique<NameLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Int) {
        result = make_unique<IntLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::Float) {
        result = make_unique<FloatLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwTrue) {
        result = make_unique<BoolLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwFalse) {
        result = make_unique<BoolLiteral>(scanner.get_context());
        scanner.move();
        goto END;
    }
    if (scanner.get_token() == Token::KwNone) {
        result = make_unique<NoneLiteral>(scanner.get_context());
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

bool Parser::is_selector(ExprPtr& result) {
    Context         context;
    vector<ExprPtr> args, keys;

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
        result = make_unique<CallExpr>(context, result, args);
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
        result = make_unique<SubscriptExpr>(context, result, keys);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
L5:
    if (scanner.get_token() == Token::Name) {
        auto name = make_unique<NameLiteral>(scanner.get_context());
        result = make_unique<MemberAccessExpr>(context, result, name);
        scanner.move();
        goto END;
    }
    throw CompilationError::InvalidSyntax;
END:
    return true;
}

bool Parser::is_list(ExprPtr& result) {
    Context         context;
    vector<ExprPtr> exprs;

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
    result = make_unique<ListLiteral>(context, exprs);
    return true;
}

bool Parser::is_function(StmtPtr& result) {
    Context                          context;
    NameLiteralPtr                   name;
    vector<unique_ptr<ParamDefExpr>> params;
    ExprPtr                          ret_type_expr;
    vector<StmtPtr>                  stmts;

    if (scanner.get_token() == Token::KwDef) {
        context = scanner.get_context();
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Name) {
        name = make_unique<NameLiteral>(scanner.get_context());
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
    result = make_unique<FuncDefStmt>(context, name, params, ret_type_expr, stmts);
    return true;
}

bool Parser::are_parameters(vector<unique_ptr<ParamDefExpr>>& result) {
    unique_ptr<ParamDefExpr> param;

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

bool Parser::is_parameter(unique_ptr<ParamDefExpr>& result) {
    NameLiteralPtr name;
    ExprPtr        type;

    if (scanner.get_token() == Token::Name) {
        name = make_unique<NameLiteral>(scanner.get_context());
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
    result = make_unique<ParamDefExpr>(name, type);
    return true;
}

bool Parser::is_if(StmtPtr& result) {
    using Condition = ExprPtr;
    using Statements = vector<StmtPtr>;
    using Branch = std::pair<Condition, Statements>;

    Context        context;
    vector<Branch> branches;
    Statements     else_stmts;

    if (scanner.get_token() == Token::KwIf) {
        context = scanner.get_context();
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
    result = make_unique<IfStmt>(context, branches, else_stmts);
    return true;
}

bool Parser::is_while(StmtPtr& result) {
    Context         context;
    ExprPtr         condition;
    vector<StmtPtr> body;

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
    result = make_unique<WhileStmt>(context, condition, body);
    return true;
}

bool Parser::is_suite(vector<StmtPtr>& result) {
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

bool Parser::is_structure(StmtPtr& result) {
    Context                      context;
    vector<unique_ptr<FieldDef>> fields;

    if (scanner.get_token() == Token::KwStruct) {
        scanner.move();
        goto L1;
    }
    return false;
L1:
    if (scanner.get_token() == Token::Name) {
        context = scanner.get_context();
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
    result = make_unique<StructDefStmt>(context, fields);
    return true;
}

bool Parser::are_fields(vector<unique_ptr<FieldDef>>& result) {
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

bool Parser::is_field_row(vector<unique_ptr<FieldDef>>& result) {
    unique_ptr<FieldDef> field;

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

bool Parser::is_field_col(vector<unique_ptr<FieldDef>>& result) {
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

bool Parser::is_field(unique_ptr<FieldDef>& result) {
    NameLiteralPtr name;
    ExprPtr        type;
    ExprPtr        init_expr;

    if (scanner.get_token() == Token::Name) {
        name = make_unique<NameLiteral>(scanner.get_context());
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
    result = make_unique<FieldDef>(name, type, init_expr);
    return true;
}

}  // namespace quirk