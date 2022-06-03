#include "ast_printer.h"
#include "fmt/ostream.h"
#include "indent_guard.h"
#include "magic_enum.hpp"

namespace quirk::util {

AstPrinter::AstPrinter(std::ostream& out, ast::TranslationUnit* tu) : out(out)
{
    for (size_t i = 0; i < tu->count_stmts(); i++) {
        tu->get_stmt(i)->accept(this);
    }
}

void AstPrinter::visit(ast::AsgStmt* node)
{
    fmt::print(out, "{}AsgStmt:\n", offset(indent));
    IndentGuard inc(indent);
    {
        fmt::print(out, "{}lvalue:\n", offset(indent));
        IndentGuard inc(indent);
        {
            node->get_lvalue()->accept(this);
        }
        if (node->get_type_expr() != nullptr) {
            fmt::print(out, "{}type:\n", offset(indent));
            IndentGuard inc(indent);
            {
                node->get_type_expr()->accept(this);
            }
        }
        if (node->get_rvalue() != nullptr) {
            fmt::print(out, "{}rvalue:\n", offset(indent));
            IndentGuard inc(indent);
            {
                node->get_rvalue()->accept(this);
            }
        }
    }
}

void AstPrinter::visit(ast::BinaryExpr* node)
{
    fmt::print(out, "{}BinaryExpr: {}\n", offset(indent), magic_enum::enum_name(node->get_kind()));
    IndentGuard inc(indent);
    {
        node->get_left()->accept(this);
        node->get_right()->accept(this);
    }
}

void AstPrinter::visit(ast::BoolLiteral* node)
{
    fmt::print(out, "{}BoolLiteral: {}\n", offset(indent), node->to_bool());
}

void AstPrinter::visit(ast::BreakStmt*)
{
    fmt::print(out, "{}BreakStmt\n", offset(indent));
}

void AstPrinter::visit(ast::CallExpr* node)
{
    fmt::print(out, "{}CallExpr:\n", offset(indent));
    IndentGuard inc(indent);
    {
        print_call(node);
    }
}

void AstPrinter::visit(ast::CallStmt* node)
{
    fmt::print(out, "{}CallStmt:\n", offset(indent));
    IndentGuard inc(indent);
    {
        print_call(node->get_expr());
    }
}

void AstPrinter::visit(ast::ContinueStmt*)
{
    fmt::print(out, "{}ContinueStmt\n", offset(indent));
}

void AstPrinter::visit(ast::FieldDefStmt* node)
{
    fmt::print(out, "{}FieldDef: '{}'\n", offset(indent), node->get_name()->get_value());
    IndentGuard inc(indent);
    {
        if (node->get_type() != nullptr) {
            fmt::print(out, "{}type:\n", offset(indent));
            IndentGuard inc(indent);
            {
                node->get_type()->accept(this);
            }
        }
        if (node->get_init_expr() != nullptr) {
            fmt::print(out, "{}init:\n", offset(indent));
            IndentGuard inc(indent);
            {
                node->get_init_expr()->accept(this);
            }
        }
    }
}

void AstPrinter::visit(ast::FloatLiteral* node)
{
    fmt::print(out, "{}FloatLiteral: {}\n", offset(indent), node->to_double());
}

void AstPrinter::visit(ast::FuncDefStmt* node)
{
    fmt::print(out, "{}FuncDefStmt: '{}'\n", offset(indent), node->get_name()->get_value());
    IndentGuard inc(indent);
    {
        auto& params = node->get_params();
        if (params.begin() != params.end()) {
            fmt::print(out, "{}params:\n", offset(indent));
            IndentGuard inc(indent);
            {
                for (auto param : params) {
                    param->accept(this);
                }
            }
        }
        if (node->get_ret_type_expr() != nullptr) {
            fmt::print(out, "{}ret:\n", offset(indent));
            IndentGuard inc(indent);
            {
                node->get_ret_type_expr()->accept(this);
            }
        }
        auto& stmts = node->get_stmts();
        if (stmts.begin() != stmts.end()) {
            fmt::print(out, "{}body:\n", offset(indent));
            IndentGuard inc(indent);
            {
                for (auto stmt : stmts) {
                    stmt->accept(this);
                }
            }
        } else {
            fmt::print(out, "{}body: <empty>\n", offset(indent));
        }
    }
}

void AstPrinter::visit(ast::IfStmt* node)
{
    fmt::print(out, "{}IfStmt:\n", offset(indent));
    IndentGuard inc(indent);
    {
        for (size_t i = 0; i < node->count_branches(); i++) {
            fmt::print(out, "{}condition:\n", offset(indent));
            IndentGuard inc(indent);
            {
                node->get_condition(i)->accept(this);
            }
            if (node->count_branch_stmts(i) > 0) {
                fmt::print(out, "{}body:\n", offset(indent));
                IndentGuard inc(indent);
                {
                    for (size_t j = 0; j < node->count_branch_stmts(i); j++) {
                        node->get_branch_stmt(i, j)->accept(this);
                    }
                }
            } else {
                fmt::print(out, "{}body: <empty>\n", offset(indent));
            }
        }
        if (node->count_else_stmts() > 0) {
            fmt::print(out, "{}else:\n", offset(indent));
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_else_stmts(); i++) {
                    node->get_else_stmt(i)->accept(this);
                }
            }
        } else {
            fmt::print(out, "{}selse: <empty>\n", offset(indent));
        }
    }
}

void AstPrinter::visit(ast::IntLiteral* node)
{
    fmt::print(out, "{}IntLiteral: {}\n", offset(indent), node->to_uint64());
}

void AstPrinter::visit(ast::ListLiteral* node)
{
    if (node->count_exprs() > 0) {
        fmt::print(out, "{}ListLiteral:\n", offset(indent));
        IndentGuard inc(indent);
        {
            for (size_t i = 0; i < node->count_exprs(); i++) {
                node->get_expr(i)->accept(this);
            }
        }
    } else {
        fmt::print(out, "{}ListLiteral: <empty>\n", offset(indent));
    }
}

void AstPrinter::visit(ast::MemberAccessExpr* node)
{
    fmt::print(out, "{}MemberAccessExpr:\n", offset(indent));
    IndentGuard inc(indent);
    {
        fmt::print(out, "{}designator:\n", offset(indent));
        {
            IndentGuard inc(indent);
            node->get_designator()->accept(this);
        }
        fmt::print(out, "{}selector:\n", offset(indent));
        {
            IndentGuard inc(indent);
            node->get_selector()->accept(this);
        }
    }
}

void AstPrinter::visit(ast::NameLiteral* node)
{
    fmt::print(out, "{}NameLiteral: '{}'\n", offset(indent), node->get_value());
}

void AstPrinter::visit(ast::NoneLiteral*)
{
    fmt::print(out, "{}NoneLiteral\n", offset(indent));
}

void AstPrinter::visit(ast::ParamDefExpr* node)
{
    fmt::print(out, "{}ParameterDef: '{}'\n", offset(indent), node->get_name()->get_value());
    IndentGuard inc(indent);
    {
        fmt::print(out, "{}type:\n", offset(indent));
        IndentGuard inc(indent);
        {
            node->get_type()->accept(this);
        }
    }
}

void AstPrinter::visit(ast::ReturnStmt* node)
{
    fmt::print(out, "{}ReturnStmt\n", offset(indent));
    IndentGuard inc(indent);
    {
        node->get_expr()->accept(this);
    }
}

void AstPrinter::visit(ast::StructDefStmt* node)
{
    fmt::print(out, "{}StructDefStmt: '{}'\n", offset(indent), node->get_name()->get_value());
    IndentGuard inc(indent);
    {
        if (node->count_fields() > 0) {
            fmt::print(out, "{}fields:\n", offset(indent));
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_fields(); i++) {
                    node->get_field(i)->accept(this);
                }
            }
        } else {
            fmt::print(out, "{}fields: <empty>\n", offset(indent));
        }
    }
}

void AstPrinter::visit(ast::SubscriptExpr* node)
{
    fmt::print(out, "{}SubscriptExpr:\n", offset(indent));
    IndentGuard inc(indent);
    {
        fmt::print(out, "{}designator:\n", offset(indent));
        {
            IndentGuard inc(indent);
            node->get_designator()->accept(this);
        }
        fmt::print(out, "{}keys:\n", offset(indent));
        {
            IndentGuard inc(indent);
            for (size_t i = 0; i < node->count_keys(); i++) {
                node->get_key(i)->accept(this);
            }
        }
    }
}

void AstPrinter::visit(ast::UnaryExpr* node)
{
    fmt::print(out, "{}UnaryExpr: {}\n", "", offset(indent),
               magic_enum::enum_name(node->get_kind()));
    IndentGuard inc(indent);
    {
        node->get_expr()->accept(this);
    }
}

void AstPrinter::visit(ast::WhileStmt* node)
{
    fmt::print(out, "{}WhileStmt:\n", offset(indent));
    IndentGuard inc(indent);
    {
        fmt::print(out, "{}condition:\n", offset(indent));
        IndentGuard inc(indent);
        {
            node->get_condition()->accept(this);
        }
        if (node->count_stmts() > 0) {
            fmt::print(out, "{}body:\n", offset(indent));
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_stmts(); i++) {
                    node->get_stmt(i)->accept(this);
                }
            }
        } else {
            fmt::print(out, "{}body: <empty>\n", offset(indent));
        }
    }
}

void AstPrinter::print_call(ast::CallExpr* node)
{
    fmt::print(out, "{}designator:\n", offset(indent));
    IndentGuard inc(indent);
    {
        node->get_designator()->accept(this);
    }
    if (node->count_args() > 0) {
        fmt::print(out, "{}args:\n", offset(indent));
        IndentGuard inc(indent);
        {
            for (size_t i = 0; i < node->count_args(); i++) {
                node->get_arg(i)->accept(this);
            }
        }
    } else {
        fmt::print(out, "{}args: <empty>\n", offset(indent));
    }
}

} // namespace quirk::util