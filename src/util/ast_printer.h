#pragma once

#include <ostream>

#include "../ast/visitor.h"
#include "fmt/ostream.h"

namespace quirk::util {

class AstPrinter : public ast::Visitor {
    std::ostream& out;
    uint64_t indent = 0;

public:
    AstPrinter(std::ostream& out, ast::TranslationUnit* tu);

    virtual void visit(ast::AsgStmt* node) override;
    virtual void visit(ast::BinaryExpr* node) override;
    virtual void visit(ast::BoolLiteral* node) override;
    virtual void visit(ast::BreakStmt* node) override;
    virtual void visit(ast::CallExpr* node) override;
    virtual void visit(ast::CallStmt* node) override;
    virtual void visit(ast::ContinueStmt* node) override;
    virtual void visit(ast::FieldDefStmt* node) override;
    virtual void visit(ast::FloatLiteral* node) override;
    virtual void visit(ast::FuncDefStmt* node) override;
    virtual void visit(ast::IfStmt* node) override;
    virtual void visit(ast::IntLiteral* node) override;
    virtual void visit(ast::ListLiteral* node) override;
    virtual void visit(ast::MemberAccessExpr* node) override;
    virtual void visit(ast::NameLiteral* node) override;
    virtual void visit(ast::NoneLiteral* node) override;
    virtual void visit(ast::ParamDefExpr* node) override;
    virtual void visit(ast::ReturnStmt* node) override;
    virtual void visit(ast::StructDefStmt* node) override;
    virtual void visit(ast::SubscriptExpr* node) override;
    virtual void visit(ast::UnaryExpr* node) override;
    virtual void visit(ast::WhileStmt* node) override;

private:
    void print_call(ast::CallExpr* node);
};

} // namespace quirk::util