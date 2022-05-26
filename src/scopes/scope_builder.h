#pragma once

#include "../ast/translation_unit.h"
#include "field.h"
#include "function.h"
#include "parameter.h"
#include "structure.h"
#include "variable.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace quirk::scopes {

using namespace std;
using namespace ast;

class ScopeBuilder : public Visitor {
    Scope module_scope;
    vector<Scope*> scopes;

    unordered_map<NameLiteral*, Declaration*> bindings;

public:
    ScopeBuilder(vector<unique_ptr<Stmt>>& stmts);

    virtual void visit(AsgStmt* node) override;
    virtual void visit(FieldDef* node) override;
    virtual void visit(FuncDefStmt* node) override;
    virtual void visit(NameLiteral* node) override;
    virtual void visit(ParamDefExpr* node) override;
    virtual void visit(StructDefStmt* node) override;

private:
    Declaration* lookup(string_view name);
    void add_builtins();
};

// class ScopeBuilder : public Visitor {
//     vector<vector<unique_ptr<ast::Decl>>> local_decls;
//     vector<unordered_map<string, ast::Decl*>> name_tables;
//     vector<ast::Function*> functions;
//     vector<ast::Structure*> structures;

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