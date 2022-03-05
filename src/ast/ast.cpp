#include "visitor.h"

namespace quirk::ast {

uint64_t quirk::ast::ProgObj::last_id = 0;

void AsgStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void NameLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void BoolLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void IntLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void FloatLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void NoneLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void ListLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void BinaryExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void UnaryExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void BreakStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void MemberAccessExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void SubscriptExpr::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void CallExprStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void ContinueStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void FuncDefStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void IfStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void ReturnStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void ParameterDef::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void WhileStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void FieldDef::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void StructDefStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Variable::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Parameter::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Function::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Structure::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Field::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Int64Type::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Float64Type::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void OpFunc::accept(Visitor* visitor) {
    return visitor->visit(this);
}

}  // namespace quirk::ast