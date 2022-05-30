#pragma once

#include "../ast/visitor.h"
#include "../compilation_error.h"

#include "field.h"
#include "function.h"
#include "module.h"
#include "parameter.h"
#include "structure.h"
#include "variable.h"

namespace quirk::scopes {

class ScopeBuilder : public ast::Visitor {
    std::unordered_map<ast::NameLiteral*, Declaration*>& bindings;

    Scope& scope;
    ast::Node* node;
    std::vector<std::unique_ptr<ScopeBuilder>> builders;

public:
    ScopeBuilder() = delete;
    ScopeBuilder(ScopeBuilder&) = delete;
    // ScopeBuilder(ScopeBuilder&&) = delete;

    ScopeBuilder(ast::Node* node, Scope& scope,
                 std::unordered_map<ast::NameLiteral*, Declaration*>& bindings);

    void process();

    virtual void visit(ast::AsgStmt* node) override;
    virtual void visit(ast::FieldDefStmt* node) override;
    virtual void visit(ast::FuncDefStmt* node) override;
    virtual void visit(ast::NameLiteral* node) override;
    virtual void visit(ast::ParamDefExpr* node) override;
    virtual void visit(ast::StructDefStmt* node) override;
    virtual void visit(ast::TranslationUnit* node) override;
};

// class ScopeBuilder : public Visitor {
//     std::vector<std::vector<std::unique_ptr<ast::Decl>>> local_decls;
//     std::vector<unordered_map<string, ast::Decl*>> name_tables;
//     std::vector<ast::Function*> functions;
//     std::vector<ast::Structure*> structures;

// public:
//     virtual void visit(ast::Module* node);

//     virtual void visit(ast::Function* node);
//     virtual void visit(ast::Structure* node);

//     virtual void visit(ast::BinaryExpr* node);
//     virtual void visit(ast::FieldDef* node);
//     virtual void visit(ast::CallExprStmt* node);
//     virtual void visit(ast::FuncDefStmt* node);
//     virtual void visit(ast::ListLiteral* node);
//     virtual void visit(ast::MemberAccessExpr* node);
//     virtual void visit(ast::NameLiteral* node);
//     virtual void visit(ast::SubscriptExpr* node);
//     virtual void visit(ast::UnaryExpr* node);

//     virtual void visit(ast::AsgStmt* node);
//     virtual void visit(ast::IfStmt* node);
//     virtual void visit(ast::ParameterDef* node);
//     virtual void visit(ast::ReturnStmt* node);
//     virtual void visit(ast::StructDefStmt* node);
//     virtual void visit(ast::WhileStmt* node);

// private:
//     ast::Decl* Find(string_view name);

//     void add_primitive_types();
//     void add_bin_op(string name, ast::Decl* left_type, ast::Decl* right_type, ast::Decl*
//     ret_type); void add_operator_funcs();
// };

} // namespace quirk::scopes