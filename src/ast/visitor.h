#pragma once

#include "fwd.h"

namespace quirk::ast {

class Visitor {
public:
    virtual void visit(AsgStmt* node) = 0;
    virtual void visit(BinaryExpr* node) = 0;
    virtual void visit(BoolLiteral* node) = 0;
    virtual void visit(BreakStmt* node) = 0;
    virtual void visit(CallExpr* node) = 0;
    virtual void visit(CallStmt* node) = 0;
    virtual void visit(ContinueStmt* node) = 0;
    virtual void visit(FieldDef* node) = 0;
    virtual void visit(FloatLiteral* node) = 0;
    virtual void visit(FuncDefStmt* node) = 0;
    virtual void visit(IfStmt* node) = 0;
    virtual void visit(IntLiteral* node) = 0;
    virtual void visit(ListLiteral* node) = 0;
    virtual void visit(MemberAccessExpr* node) = 0;
    virtual void visit(NameLiteral* node) = 0;
    virtual void visit(NoneLiteral* node) = 0;
    virtual void visit(ParamDefExpr* node) = 0;
    virtual void visit(ReturnStmt* node) = 0;
    virtual void visit(StructDefStmt* node) = 0;
    virtual void visit(SubscriptExpr* node) = 0;
    virtual void visit(UnaryExpr* node) = 0;
    virtual void visit(WhileStmt* node) = 0;
};

}  // namespace quirk::ast