#pragma once

#include <ostream>
#include "../ast/headers.h"
#include "fmt/ostream.h"
#include "indent_guard.h"

namespace quirk::util {

using namespace std;
using namespace ast;

class AstPrinter : public Visitor {
    ostream& out;
    int      indent = 0;

public:
    AstPrinter(ostream& out, vector<StmtPtr>& stmts);

    virtual void visit(AsgStmt* node) override;
    virtual void visit(BinaryExpr* node) override;
    virtual void visit(BoolLiteral* node) override;
    virtual void visit(BreakStmt* node) override;
    virtual void visit(CallExpr* node) override;
    virtual void visit(CallStmt* node) override;
    virtual void visit(ContinueStmt* node) override;
    virtual void visit(FieldDef* node) override;
    virtual void visit(FloatLiteral* node) override;
    virtual void visit(FuncDefStmt* node) override;
    virtual void visit(IfStmt* node) override;
    virtual void visit(IntLiteral* node) override;
    virtual void visit(ListLiteral* node) override;
    virtual void visit(MemberAccessExpr* node) override;
    virtual void visit(NameLiteral* node) override;
    virtual void visit(NoneLiteral* node) override;
    virtual void visit(ParamDefExpr* node) override;
    virtual void visit(ReturnStmt* node) override;
    virtual void visit(StructDefStmt* node) override;
    virtual void visit(SubscriptExpr* node) override;
    virtual void visit(UnaryExpr* node) override;
    virtual void visit(WhileStmt* node) override;

private:
    void print_call(CallExpr* node);

    template <typename S, typename... Args>
    void print(const S& format_str, Args&&... args)
    {
        for (auto i = 0; i < indent; i++) {
            fmt::print(out, "    ");
        }
        fmt::print(out, format_str, args...);
    }
};

}  // namespace quirk::util