#pragma once

#include "../ast/visitor.h"

#include "field.h"
#include "function.h"
#include "module.h"
#include "parameter.h"
#include "structure.h"
#include "variable.h"

namespace quirk::scopes {

// 1. builds scopes
// 2. binds ast nodes to corresponding declarations
// 3. finds declaration order errors
class ScopeBuilder : public ast::Visitor {
    std::unordered_map<ast::Node*, Declaration*>& bindings;

    Scope* local_scope;
    ast::Node* root_node;
    std::vector<ScopeBuilder> future_work;

    ScopeBuilder(ast::Node* root_node, Scope* local_scope,
                 std::unordered_map<ast::Node*, Declaration*>& bindings);

public:
    ScopeBuilder(ast::TranslationUnit* unit, Scope& global_scope,
                 std::unordered_map<ast::Node*, Declaration*>& bindings);

    void process();

    virtual void visit(ast::AsgStmt* node) override;
    virtual void visit(ast::BinaryExpr* node) override;
    virtual void visit(ast::FieldDefStmt* node) override;
    virtual void visit(ast::FuncDefStmt* node) override;
    virtual void visit(ast::NameLiteral* node) override;
    virtual void visit(ast::ParamDefExpr* node) override;
    virtual void visit(ast::StructDefStmt* node) override;
    virtual void visit(ast::UnaryExpr* node) override;
};

} // namespace quirk::scopes