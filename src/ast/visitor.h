#pragma once

#include "fwd.h"

namespace quirk::ast {

class Visitor {
public:
    virtual void visit(AsgStmt* node);
    virtual void visit(BinaryExpr* node);
    virtual void visit(BoolLiteral* node);
    virtual void visit(BreakStmt* node);
    virtual void visit(CallExpr* node);
    virtual void visit(CallStmt* node);
    virtual void visit(ContinueStmt* node);
    virtual void visit(FieldDef* node);
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
    virtual void visit(UnaryExpr* node);
    virtual void visit(WhileStmt* node);
};

}  // namespace quirk::ast