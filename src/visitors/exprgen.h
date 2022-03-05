#pragma once
#include "ast/visitor.h"
#include "declgen.h"

namespace quirk {

// ExprGen generates llvm code for expressions and stores the result in the `value` field
class ExprGen : public ast::Visitor {
    llvm::LLVMContext& context;
    llvm::IRBuilder<>& builder;
    DeclGen& decls;

    llvm::Value* value = nullptr;

public:
    ExprGen(DeclGen& decls, ast::ProgObj* item)
        : context(decls.get_context()), builder(decls.get_builder()), decls(decls) {
        item->accept(this);
        assert(value != nullptr);
    }

    auto get_value() { return value; }

    void visit(ast::Function* item) override;
    void visit(ast::Variable* item) override;
    void visit(ast::Parameter* item) override;

    void visit(ast::BinaryExpr* item) override;
    void visit(ast::CallExprStmt* item) override;
    void visit(ast::NameLiteral* item) override;
    void visit(ast::IntLiteral* item) override;
    void visit(ast::FloatLiteral* item) override;
};

}  // namespace quirk