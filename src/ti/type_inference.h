#pragma once

#include <assert.h>
#include <unordered_map>

#include "../ast/visitor.h"
#include "../compilation_error.h"
#include "../scopes/declaration.h"
#include "../util/operator_table.h"

namespace quirk::ti {

class TypeInference : public ast::Visitor {
    std::unordered_map<ast::Node*, scopes::Declaration*>& bindings;

    std::unordered_map<scopes::Declaration*, scopes::Declaration*>& type_table;
    scopes::Declaration* cur_type = nullptr;

public:
    TypeInference(ast::Node* cur_node,
                  std::unordered_map<ast::Node*, scopes::Declaration*>& bindings,
                  std::unordered_map<scopes::Declaration*, scopes::Declaration*>& type_table)
        : bindings(bindings), type_table(type_table)
    {
        cur_node->accept(this);
    }

    auto get_type() { return cur_type; }

    virtual void visit(ast::AsgStmt* node);
    virtual void visit(ast::BinaryExpr* node);
    // virtual void visit(ast::BoolLiteral* node);
    // virtual void visit(ast::BreakStmt* node);
    // virtual void visit(ast::CallExpr* node);
    // virtual void visit(ast::CallStmt* node);
    // virtual void visit(ast::ContinueStmt* node);
    // virtual void visit(ast::FieldDefStmt* node);
    // virtual void visit(ast::FloatLiteral* node);
    // virtual void visit(ast::FuncDefStmt* node);
    // virtual void visit(ast::IfStmt* node);
    // virtual void visit(ast::IntLiteral* node);
    // virtual void visit(ast::ListLiteral* node);
    // virtual void visit(ast::MemberAccessExpr* node);
    // virtual void visit(ast::NameLiteral* node);
    // virtual void visit(ast::NoneLiteral* node);
    // virtual void visit(ast::ParamDefExpr* node);
    // virtual void visit(ast::ReturnStmt* node);
    // virtual void visit(ast::StructDefStmt* node);
    // virtual void visit(ast::SubscriptExpr* node);
    // virtual void visit(ast::UnaryExpr* node);
    // virtual void visit(ast::WhileStmt* node);
};

} // namespace quirk::ti