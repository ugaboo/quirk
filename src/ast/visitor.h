#pragma once

#include "asg_stmt.h"
#include "binary_expr.h"
#include "bool_literal.h"
#include "break_stmt.h"
#include "call_expr.h"
#include "call_stmt.h"
#include "continue_stmt.h"
#include "field_def_stmt.h"
#include "float_literal.h"
#include "func_def_stmt.h"
#include "if_stmt.h"
#include "int_literal.h"
#include "list_literal.h"
#include "member_access_expr.h"
#include "name_literal.h"
#include "none_literal.h"
#include "param_def_expr.h"
#include "return_stmt.h"
#include "struct_def_stmt.h"
#include "subscript_expr.h"
#include "translation_unit.h"
#include "unary_expr.h"
#include "while_stmt.h"

namespace quirk::ast {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void visit(AsgStmt* node);
    virtual void visit(BinaryExpr* node);
    virtual void visit(BoolLiteral* node);
    virtual void visit(BreakStmt* node);
    virtual void visit(CallExpr* node);
    virtual void visit(CallStmt* node);
    virtual void visit(ContinueStmt* node);
    virtual void visit(FieldDefStmt* node);
    virtual void visit(FloatLiteral* node);
    virtual void visit(FuncDefStmt* node);
    virtual void visit(IfStmt* node);
    virtual void visit(IntLiteral* node);
    virtual void visit(ListLiteral* node);
    virtual void visit(MemberAccessExpr* node);
    virtual void visit(NameLiteral* node);
    virtual void visit(NoneLiteral* node);
    virtual void visit(ParamDefExpr* node);
    virtual void visit(ReturnStmt* node);
    virtual void visit(StructDefStmt* node);
    virtual void visit(SubscriptExpr* node);
    virtual void visit(TranslationUnit* node);
    virtual void visit(UnaryExpr* node);
    virtual void visit(WhileStmt* node);
};

} // namespace quirk::ast