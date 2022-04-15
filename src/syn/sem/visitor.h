#pragma once

#include "ast/asg_stmt.h"
#include "ast/basic_type.h"
#include "ast/binary_expr.h"
#include "ast/bool_literal.h"
#include "ast/break_stmt.h"
#include "ast/call_expr_stmt.h"
#include "ast/continue_stmt.h"
#include "ast/field.h"
#include "ast/field_def.h"
#include "ast/float_literal.h"
#include "ast/func_def_stmt.h"
#include "ast/function.h"
#include "ast/if_stmt.h"
#include "ast/int_literal.h"
#include "ast/list_literal.h"
#include "ast/member_access_expr.h"
#include "ast/module.h"
#include "ast/name_literal.h"
#include "ast/none_literal.h"
#include "ast/op_func.h"
#include "ast/parameter.h"
#include "ast/parameter_def.h"
#include "ast/return_stmt.h"
#include "ast/struct_def_stmt.h"
#include "ast/structure.h"
#include "ast/subscript_expr.h"
#include "ast/unary_expr.h"
#include "ast/variable.h"
#include "ast/while_stmt.h"

namespace quirk {

class Visitor {
public:
    virtual void visit(ast::AsgStmt* node) {}
    virtual void visit(ast::BinaryExpr* node) {}
    virtual void visit(ast::BoolLiteral* node) {}
    virtual void visit(ast::BreakStmt* node) {}
    virtual void visit(ast::CallExprStmt* node) {}
    virtual void visit(ast::ContinueStmt* node) {}
    virtual void visit(ast::Field* node) {}
    virtual void visit(ast::FieldDef* node) {}
    virtual void visit(ast::Float64Type* node) {}
    virtual void visit(ast::FloatLiteral* node) {}
    virtual void visit(ast::FuncDefStmt* node) {}
    virtual void visit(ast::Function* node) {}
    virtual void visit(ast::IfStmt* node) {}
    virtual void visit(ast::Int64Type* node) {}
    virtual void visit(ast::IntLiteral* node) {}
    virtual void visit(ast::ListLiteral* node) {}
    virtual void visit(ast::MemberAccessExpr* node) {}
    virtual void visit(ast::Module* node) {}
    virtual void visit(ast::NameLiteral* node) {}
    virtual void visit(ast::NoneLiteral* node) {}
    virtual void visit(ast::OpFunc* node) {}
    virtual void visit(ast::Parameter* node) {}
    virtual void visit(ast::ParameterDef* node) {}
    virtual void visit(ast::ReturnStmt* node) {}
    virtual void visit(ast::StructDefStmt* node) {}
    virtual void visit(ast::Structure* node) {}
    virtual void visit(ast::SubscriptExpr* node) {}
    virtual void visit(ast::UnaryExpr* node) {}
    virtual void visit(ast::Variable* node) {}
    virtual void visit(ast::WhileStmt* node) {}
};

inline void ast::AsgStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::BinaryExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::BoolLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::BreakStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::CallExprStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::ContinueStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Field::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::FieldDef::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Float64Type::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::FloatLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::FuncDefStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Function::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::IfStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Int64Type::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::IntLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::ListLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::MemberAccessExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::NameLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::NoneLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::OpFunc::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Parameter::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::ParameterDef::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::ReturnStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::StructDefStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Structure::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::SubscriptExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::UnaryExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::Variable::accept(Visitor* visitor) {
    return visitor->visit(this);
}

inline void ast::WhileStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

}  // namespace quirk