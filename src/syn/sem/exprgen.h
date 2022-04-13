#pragma once
#include "declgen.h"
#include "visitor.h"

namespace quirk {

// ExprGen generates llvm code for expressions and stores the result in the `value` field
class ExprGen : public Visitor {
    llvm::LLVMContext& context;
    llvm::IRBuilder<>& builder;
    DeclGen& decls;

    llvm::Value* value = nullptr;

public:
    ExprGen(DeclGen& decls, ast::Node* node)
        : context(decls.get_context()), builder(decls.get_builder()), decls(decls) {
        node->accept(this);
        assert(value != nullptr);
    }

    auto get_value() { return value; }

    void visit(ast::Function* node) override;
    void visit(ast::Variable* node) override;
    void visit(ast::Parameter* node) override;

    void visit(ast::BinaryExpr* node) override;
    void visit(ast::CallExprStmt* node) override;
    void visit(ast::NameLiteral* node) override;
    void visit(ast::IntLiteral* node) override;
    void visit(ast::FloatLiteral* node) override;
};

}  // namespace quirk