#include "ast_printer.h"
#include "fmt/ostream.h"
#include "magic_enum.hpp"

namespace quirk::util {

using fmt::print;

AstPrinter::AstPrinter(std::ostream& out, vector<StmtPtr>& stmts) : out(out)
{
    for (auto& s : stmts) {
        s->accept(this);
    }
}

void AstPrinter::visit(AsgStmt* node)
{
    print("AsgStmt:\n");
    IndentGuard inc(indent);
    {
        print("lvalue:\n");
        IndentGuard inc(indent);
        {
            node->get_lvalue()->accept(this);
        }
        if (node->get_type_expr() != nullptr) {
            print("type:\n");
            IndentGuard inc(indent);
            {
                node->get_type_expr()->accept(this);
            }
        }
        if (node->get_rvalue() != nullptr) {
            print("rvalue:\n");
            IndentGuard inc(indent);
            {
                node->get_rvalue()->accept(this);
            }
        }
    }
}

void AstPrinter::visit(BinaryExpr* node)
{
    print("BinaryExpr: {}\n", magic_enum::enum_name(node->get_kind()));
    IndentGuard inc(indent);
    {
        node->get_left()->accept(this);
        node->get_right()->accept(this);
    }
}

void AstPrinter::visit(BoolLiteral* node)
{
    print("BoolLiteral: {}\n", node->get_value());
}

void AstPrinter::visit(BreakStmt*)
{
    print("BreakStmt\n");
}

void AstPrinter::visit(CallExpr* node)
{
    print("CallExpr:\n");
    IndentGuard inc(indent);
    {
        print_call(node);
    }
}

void AstPrinter::visit(CallStmt* node)
{
    print("CallStmt:\n");
    IndentGuard inc(indent);
    {
        print_call(node->get_expr());
    }
}

void AstPrinter::visit(ContinueStmt*)
{
    print("ContinueStmt\n");
}

void AstPrinter::visit(FieldDef* node)
{
    print("FieldDef: '{}'\n", node->get_name());
    IndentGuard inc(indent);
    {
        if (node->get_type() != nullptr) {
            print("type:\n");
            IndentGuard inc(indent);
            {
                node->get_type()->accept(this);
            }
        }
        if (node->get_init_expr() != nullptr) {
            print("init:\n");
            IndentGuard inc(indent);
            {
                node->get_init_expr()->accept(this);
            }
        }
    }
}

void AstPrinter::visit(FloatLiteral* node)
{
    print("FloatLiteral: {}\n", node->get_value());
}

void AstPrinter::visit(FuncDefStmt* node)
{
    print("FuncDefStmt: '{}'\n", node->get_name());
    IndentGuard inc(indent);
    {
        if (node->count_params() > 0) {
            print("params:\n");
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_params(); i++) {
                    node->get_param(i)->accept(this);
                }
            }
        }
        if (node->get_ret_type_expr() != nullptr) {
            print("ret:\n");
            IndentGuard inc(indent);
            {
                node->get_ret_type_expr()->accept(this);
            }
        }
        if (node->count_stmts() > 0) {
            print("body:\n");
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_stmts(); i++) {
                    node->get_stmt(i)->accept(this);
                }
            }
        }
        else {
            print("body: <empty>\n");
        }
    }
}

void AstPrinter::visit(IfStmt* node)
{
    print("IfStmt:\n");
    IndentGuard inc(indent);
    {
        for (size_t i = 0; i < node->count_branches(); i++) {
            print("condition:\n");
            IndentGuard inc(indent);
            {
                node->get_condition(i)->accept(this);
            }
            if (node->count_branch_stmts(i) > 0) {
                print("body:\n");
                IndentGuard inc(indent);
                {
                    for (size_t j = 0; j < node->count_branch_stmts(i); j++) {
                        node->get_branch_stmt(i, j)->accept(this);
                    }
                }
            }
            else {
                print("body: <empty>\n");
            }
        }
        if (node->count_else_stmts() > 0) {
            print("else:\n");
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_else_stmts(); i++) {
                    node->get_else_stmt(i)->accept(this);
                }
            }
        }
        else {
            print("selse: <empty>\n");
        }
    }
}

void AstPrinter::visit(IntLiteral* node)
{
    print("IntLiteral: {}\n", node->get_value());
}

void AstPrinter::visit(ListLiteral* node)
{
    if (node->count_exprs() > 0) {
        print("ListLiteral:\n");
        IndentGuard inc(indent);
        {
            for (size_t i = 0; i < node->count_exprs(); i++) {
                node->get_expr(i)->accept(this);
            }
        }
    }
    else {
        print("ListLiteral: <empty>\n");
    }
}

void AstPrinter::visit(MemberAccessExpr* node)
{
    print("MemberAccessExpr:\n");
    IndentGuard inc(indent);
    {
        print("designator:\n");
        {
            IndentGuard inc(indent);
            node->get_designator()->accept(this);
        }
        print("selector:\n");
        {
            IndentGuard inc(indent);
            node->get_selector()->accept(this);
        }
    }
}

void AstPrinter::visit(NameLiteral* node)
{
    print("NameLiteral: '{}'\n", node->get_value());
}

void AstPrinter::visit(NoneLiteral*)
{
    print("NoneLiteral\n");
}

void AstPrinter::visit(ParamDefExpr* node)
{
    print("ParameterDef: '{}'\n", node->get_name());
    IndentGuard inc(indent);
    {
        print("type:\n");
        IndentGuard inc(indent);
        {
            node->get_type()->accept(this);
        }
    }
}

void AstPrinter::visit(ReturnStmt* node)
{
    print("ReturnStmt\n");
    IndentGuard inc(indent);
    {
        node->get_expr()->accept(this);
    }
}

void AstPrinter::visit(StructDefStmt* node)
{
    print("StructDefStmt: '{}'\n", node->get_name());
    IndentGuard inc(indent);
    {
        if (node->count_fields() > 0) {
            print("fields:\n");
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_fields(); i++) {
                    node->get_field(i)->accept(this);
                }
            }
        }
        else {
            print("fields: <empty>\n");
        }
    }
}

void AstPrinter::visit(SubscriptExpr* node)
{
    print("SubscriptExpr:\n");
    IndentGuard inc(indent);
    {
        print("designator:\n");
        {
            IndentGuard inc(indent);
            node->get_designator()->accept(this);
        }
        print("keys:\n");
        {
            IndentGuard inc(indent);
            for (size_t i = 0; i < node->count_keys(); i++) {
                node->get_key(i)->accept(this);
            }
        }
    }
}

void AstPrinter::visit(UnaryExpr* node)
{
    print("UnaryExpr: {}\n", magic_enum::enum_name(node->get_kind()));
    IndentGuard inc(indent);
    {
        node->get_expr()->accept(this);
    }
}

void AstPrinter::visit(WhileStmt* node)
{
    print("WhileStmt:\n");
    IndentGuard inc(indent);
    {
        print("condition:\n");
        IndentGuard inc(indent);
        {
            node->get_condition()->accept(this);
        }
        if (node->count_stmts() > 0) {
            print("body:\n");
            IndentGuard inc(indent);
            {
                for (size_t i = 0; i < node->count_stmts(); i++) {
                    node->get_stmt(i)->accept(this);
                }
            }
        }
        else {
            print("body: <empty>\n");
        }
    }
}

void AstPrinter::print_call(CallExpr* node)
{
    print("designator:\n");
    IndentGuard inc(indent);
    {
        node->get_designator()->accept(this);
    }
    if (node->count_args() > 0) {
        print("args:\n");
        IndentGuard inc(indent);
        {
            for (size_t i = 0; i < node->count_args(); i++) {
                node->get_arg(i)->accept(this);
            }
        }
    }
    else {
        print("args: <empty>\n");
    }
}

}  // namespace quirk::util