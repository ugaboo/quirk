#pragma once
#include "visitor.h"

namespace quirk {

using std::unique_ptr;

class AstPrinter : public Visitor {
    std::ostream& out;
    int indent = 0;

public:
    AstPrinter(std::ostream& out) : out(out) {}

    virtual void visit(ast::Module* node);

    virtual void visit(ast::Field* node);
    virtual void visit(ast::Function* node);
    virtual void visit(ast::Structure* node);
    virtual void visit(ast::Variable* node);
    virtual void visit(ast::Parameter* node);

    virtual void visit(ast::BinaryExpr* node);
    virtual void visit(ast::BoolLiteral* node);
    virtual void visit(ast::BreakStmt* node);
    virtual void visit(ast::ContinueStmt* node);
    virtual void visit(ast::FieldDef* node);
    virtual void visit(ast::FloatLiteral* node);
    virtual void visit(ast::CallExprStmt* node);
    virtual void visit(ast::FuncDefStmt* node);
    virtual void visit(ast::IntLiteral* node);
    virtual void visit(ast::ListLiteral* node);
    virtual void visit(ast::MemberAccessExpr* node);
    virtual void visit(ast::NameLiteral* node);
    virtual void visit(ast::NoneLiteral* node);
    virtual void visit(ast::SubscriptExpr* node);
    virtual void visit(ast::UnaryExpr* node);

    virtual void visit(ast::AsgStmt* node);
    virtual void visit(ast::IfStmt* node);
    virtual void visit(ast::ParameterDef* node);
    virtual void visit(ast::ReturnStmt* node);
    virtual void visit(ast::StructDefStmt* node);
    virtual void visit(ast::WhileStmt* node);

    virtual void visit(ast::Int64Type* node);
    virtual void visit(ast::Float64Type* node);

private:
    void print_indent();
};

}  // namespace quirk