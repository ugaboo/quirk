#pragma once
#include "ast/visitor.h"

namespace quirk {

using std::unique_ptr;

class AstPrinter : public ast::Visitor {
    std::ostream& out;
    int ln = 1;
    int indent = 0;

public:
    AstPrinter(std::ostream& out) : out(out) {}

    virtual void visit(ast::Module* item);

    virtual void visit(ast::Field* item);
    virtual void visit(ast::Function* item);
    virtual void visit(ast::Structure* item);
    virtual void visit(ast::Variable* item);
    virtual void visit(ast::Parameter* item);

    virtual void visit(ast::BinaryExpr* item);
    virtual void visit(ast::BoolLiteral* item);
    virtual void visit(ast::BreakStmt* item);
    virtual void visit(ast::ContinueStmt* item);
    virtual void visit(ast::FieldDef* item);
    virtual void visit(ast::FloatLiteral* item);
    virtual void visit(ast::CallExprStmt* item);
    virtual void visit(ast::FuncDefStmt* item);
    virtual void visit(ast::IntLiteral* item);
    virtual void visit(ast::ListLiteral* item);
    virtual void visit(ast::MemberAccessExpr* item);
    virtual void visit(ast::NameLiteral* item);
    virtual void visit(ast::NoneLiteral* item);
    virtual void visit(ast::SubscriptExpr* item);
    virtual void visit(ast::UnaryExpr* item);

    virtual void visit(ast::AsgStmt* item);
    virtual void visit(ast::IfStmt* item);
    virtual void visit(ast::ParameterDef* item);
    virtual void visit(ast::ReturnStmt* item);
    virtual void visit(ast::StructDefStmt* item);
    virtual void visit(ast::WhileStmt* item);

    virtual void visit(ast::Int64Type* item);
    virtual void visit(ast::Float64Type* item);

private:
    void print_indent();
};

}  // namespace quirk