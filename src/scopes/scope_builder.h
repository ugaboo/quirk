#pragma once

#include "../ast/visitor.h"

#include "field.h"
#include "function.h"
#include "module.h"
#include "parameter.h"
#include "structure.h"
#include "variable.h"

namespace quirk::scopes {

class ScopeBuilder : public ast::Visitor {
    std::unordered_map<ast::NameLiteral*, Declaration*>& name_table;

    Scope* local_scope;
    ast::Node* root_node;
    std::vector<ScopeBuilder> future_work;

    ScopeBuilder(ast::Node* root_node, Scope* local_scope,
                 std::unordered_map<ast::NameLiteral*, Declaration*>& name_table);

public:
    ScopeBuilder(ast::TranslationUnit* unit, Scope& global_scope,
                 std::unordered_map<ast::NameLiteral*, Declaration*>& name_table);

    void process();

    virtual void visit(ast::AsgStmt* node) override;
    virtual void visit(ast::FieldDefStmt* node) override;
    virtual void visit(ast::FuncDefStmt* node) override;
    virtual void visit(ast::NameLiteral* node) override;
    virtual void visit(ast::ParamDefExpr* node) override;
    virtual void visit(ast::StructDefStmt* node) override;
};

} // namespace quirk::scopes