#include "visitor.h"
#include "headers.h"

namespace quirk::ast {

void Visitor::visit(AsgStmt* node)
{
    if (node->get_rvalue() != nullptr) {
        node->get_rvalue()->accept(this);
    }
    if (node->get_type_expr() != nullptr) {
        node->get_type_expr()->accept(this);
    }
    node->get_lvalue()->accept(this);
}

void Visitor::visit(BinaryExpr* node)
{
    node->get_left()->accept(this);
    node->get_right()->accept(this);
}

void Visitor::visit(BoolLiteral* node) {}

void Visitor::visit(BreakStmt* node) {}

void Visitor::visit(CallExpr* node)
{
    node->get_designator()->accept(this);
    for (size_t i = 0; i < node->count_args(); i++) {
        node->get_arg(i)->accept(this);
    }
}

void Visitor::visit(CallStmt* node)
{
    node->get_expr()->accept(this);
}

void Visitor::visit(ContinueStmt* node) {}

void Visitor::visit(FieldDef* node)
{
    node->get_init_expr()->accept(this);
    node->get_type()->accept(this);
    node->get_name()->accept(this);
}

void Visitor::visit(FloatLiteral* node) {}

void Visitor::visit(FuncDefStmt* node)
{
    node->get_name()->accept(this);
    node->get_ret_type_expr()->accept(this);
    for (size_t i = 0; i < node->count_params(); i++) {
        node->get_param(i)->accept(this);
    }
    for (size_t i = 0; i < node->count_stmts(); i++) {
        node->get_stmt(i)->accept(this);
    }
}

void Visitor::visit(IfStmt* node)
{
    for (size_t i = 0; i < node->count_branches(); i++) {
        node->get_condition(i)->accept(this);
        for (size_t j = 0; j < node->count_branch_stmts(i); j++) {
            node->get_branch_stmt(i, j)->accept(this);
        }
    }
    for (size_t i = 0; i < node->count_else_stmts(); i++) {
        node->get_else_stmt(i)->accept(this);
    }
}

void Visitor::visit(IntLiteral* node) {}

void Visitor::visit(ListLiteral* node)
{
    for (size_t i = 0; i < node->count_exprs(); i++) {
        node->get_expr(i)->accept(this);
    }
}

void Visitor::visit(MemberAccessExpr* node)
{
    node->get_designator()->accept(this);
    node->get_selector()->accept(this);
}

void Visitor::visit(NameLiteral* node) {}

void Visitor::visit(NoneLiteral* node) {}

void Visitor::visit(ParamDefExpr* node)
{
    node->get_name()->accept(this);
    node->get_type()->accept(this);
}

void Visitor::visit(ReturnStmt* node)
{
    if (node->get_expr() != nullptr) {
        node->get_expr()->accept(this);
    }
}

void Visitor::visit(StructDefStmt* node)
{
    node->get_name()->accept(this);
    for (size_t i = 0; i < node->count_fields(); i++) {
        node->get_field(i)->accept(this);
    }
}

void Visitor::visit(SubscriptExpr* node)
{
    node->get_designator()->accept(this);
    for (size_t i = 0; i < node->count_keys(); i++) {
        node->get_key(i)->accept(this);
    }
}

void Visitor::visit(UnaryExpr* node)
{
    node->get_expr()->accept(this);
}

void Visitor::visit(WhileStmt* node)
{
    node->get_condition()->accept(this);
    for (size_t i = 0; i < node->count_stmts(); i++) {
        node->get_stmt(i)->accept(this);
    }
}

} // namespace quirk::ast