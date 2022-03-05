#pragma once

#include "bool_literal.h"
#include "float_literal.h"
#include "int_literal.h"
#include "list_literal.h"
#include "name_literal.h"
#include "none_literal.h"

#include "binary_expr.h"
#include "call_expr_stmt.h"
#include "member_access_expr.h"
#include "subscript_expr.h"
#include "unary_expr.h"

#include "asg_stmt.h"
#include "break_stmt.h"
#include "continue_stmt.h"
#include "func_def_stmt.h"
#include "if_stmt.h"
#include "return_stmt.h"
#include "struct_def_stmt.h"
#include "while_stmt.h"

#include "field_def.h"
#include "parameter_def.h"

#include "field.h"
#include "function.h"
#include "module.h"
#include "op_func.h"

#include "parameter.h"
#include "structure.h"
#include "variable.h"

#include "primitive_types.h"

namespace quirk::ast {

class Visitor {
public:
    virtual void visit(Module*) {}

    virtual void visit(Field*) {}
    virtual void visit(Function*) {}
    virtual void visit(Structure*) {}
    virtual void visit(Variable*) {}
    virtual void visit(Parameter*) {}
    virtual void visit(OpFunc*) {}

    virtual void visit(BinaryExpr*) {}
    virtual void visit(BoolLiteral*) {}
    virtual void visit(BreakStmt*) {}
    virtual void visit(ContinueStmt*) {}
    virtual void visit(FieldDef*) {}
    virtual void visit(FloatLiteral*) {}
    virtual void visit(CallExprStmt*) {}
    virtual void visit(FuncDefStmt*) {}
    virtual void visit(IntLiteral*) {}
    virtual void visit(ListLiteral*) {}
    virtual void visit(MemberAccessExpr*) {}
    virtual void visit(NameLiteral*) {}
    virtual void visit(NoneLiteral*) {}
    virtual void visit(SubscriptExpr*) {}
    virtual void visit(UnaryExpr*) {}

    virtual void visit(AsgStmt*) {}
    virtual void visit(IfStmt*) {}
    virtual void visit(ParameterDef*) {}
    virtual void visit(ReturnStmt*) {}
    virtual void visit(StructDefStmt*) {}
    virtual void visit(WhileStmt*) {}

    virtual void visit(Int64Type*) {}
    virtual void visit(Float64Type*) {}
};

}  // namespace quirk::ast