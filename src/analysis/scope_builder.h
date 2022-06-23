#pragma once

#include "../ast/visitor.h"
#include "../scopes/field.h"
#include "../scopes/function.h"
#include "../scopes/module.h"
#include "../scopes/parameter.h"
#include "../scopes/structure.h"
#include "../scopes/variable.h"

namespace quirk::analysis {

class ScopeBuilder : public ast::Visitor {
public:
    std::unique_ptr<scopes::Module> build(ast::TranslationUnit* node);

private:
    std::unique_ptr<scopes::Function> build(ast::FuncDefStmt* node);
    std::unique_ptr<scopes::Structure> build(ast::StructDefStmt* node);

    virtual void visit(ast::AsgStmt* node) override;
    virtual void visit(ast::FieldDefStmt* node) override;
    virtual void visit(ast::FuncDefStmt* node) override;
    virtual void visit(ast::ParamDefExpr* node) override;
    virtual void visit(ast::StructDefStmt* node) override;

    std::string_view check_name(ast::NameLiteral* node);

private:
    scopes::Scope scope;
};

} // namespace quirk::analysis