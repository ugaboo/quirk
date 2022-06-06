#include "visitor.h"

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
    for (auto arg : node->get_args()) {
        arg->accept(this);
    }
}

void Visitor::visit(CallStmt* node)
{
    auto expr = node->get_expr();

    expr->get_designator()->accept(this);
    for (auto arg : expr->get_args()) {
        arg->accept(this);
    }
}

void Visitor::visit(ContinueStmt* node) {}

void Visitor::visit(FieldDefStmt* node)
{
    node->get_init_expr()->accept(this);
    node->get_type()->accept(this);
    node->get_name()->accept(this);
}

void Visitor::visit(FloatLiteral* node) {}

void Visitor::visit(FuncDefStmt* node)
{
    node->get_name()->accept(this);
    if (node->get_ret_type_expr() != nullptr) {
        node->get_ret_type_expr()->accept(this);
    }
    for (auto param : node->get_params()) {
        param->accept(this);
    }
    for (auto stmt : node->get_stmts()) {
        stmt->accept(this);
    }
}

void Visitor::visit(IfStmt* node)
{
    for (auto branch : node->get_branches()) {
        branch->get_condition()->accept(this);
        for (auto stmt : branch->get_stmts()) {
            stmt->accept(this);
        }
    }
    for (auto stmt : node->get_else_stmts()) {
        stmt->accept(this);
    }
}

void Visitor::visit(IntLiteral* node) {}

void Visitor::visit(ListLiteral* node)
{
    for (auto expr : node->get_exprs()) {
        expr->accept(this);
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
    for (auto field : node->get_fields()) {
        field->accept(this);
    }
}

void Visitor::visit(SubscriptExpr* node)
{
    node->get_designator()->accept(this);
    for (auto key : node->get_keys()) {
        key->accept(this);
    }
}

void Visitor::visit(TranslationUnit* node)
{
    for (auto stmt : node->get_stmts()) {
        stmt->accept(this);
    }
}

void Visitor::visit(UnaryExpr* node)
{
    node->get_expr()->accept(this);
}

void Visitor::visit(WhileStmt* node)
{
    node->get_condition()->accept(this);
    for (auto stmt : node->get_stmts()) {
        stmt->accept(this);
    }
}

} // namespace quirk::ast