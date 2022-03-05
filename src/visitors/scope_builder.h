#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "ast/visitor.h"

namespace quirk {

using std::string;
using std::string_view;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

class ScopeBuilder : public ast::Visitor {
    vector<vector<unique_ptr<ast::Decl>>> local_decls;
    vector<unordered_map<string, ast::Decl*>> name_tables;
    vector<ast::Function*> functions;
    vector<ast::Structure*> structures;

public:
    virtual void visit(ast::Module* item);

    virtual void visit(ast::Function* item);
    virtual void visit(ast::Structure* item);

    virtual void visit(ast::BinaryExpr* item);
    virtual void visit(ast::FieldDef* item);
    virtual void visit(ast::CallExprStmt* item);
    virtual void visit(ast::FuncDefStmt* item);
    virtual void visit(ast::ListLiteral* item);
    virtual void visit(ast::MemberAccessExpr* item);
    virtual void visit(ast::NameLiteral* item);
    virtual void visit(ast::SubscriptExpr* item);
    virtual void visit(ast::UnaryExpr* item);

    virtual void visit(ast::AsgStmt* item);
    virtual void visit(ast::IfStmt* item);
    virtual void visit(ast::ParameterDef* item);
    virtual void visit(ast::ReturnStmt* item);
    virtual void visit(ast::StructDefStmt* item);
    virtual void visit(ast::WhileStmt* item);

private:
    ast::Decl* Find(string_view name);

    void add_primitive_types();
    void add_bin_op(string name, ast::Decl* left_type, ast::Decl* right_type, ast::Decl* ret_type);
    void add_operator_funcs();
};

}  // namespace quirk