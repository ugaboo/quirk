#pragma once
#include "ast/visitor.h"
#include "declgen.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

namespace quirk {

using std::map;
using std::string;
using std::string_view;
using std::unique_ptr;

// CodeGen generates llvm code for the module, functions and statements
class CodeGen : public ast::Visitor {
    string filename;

    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;

    unique_ptr<llvm::Module> module;

    unique_ptr<DeclGen> decls;

    llvm::Value* llvm_value;

public:
    CodeGen(string filename);

    void visit(ast::Module* item) override;
    void visit(ast::FuncDefStmt* item) override;
    void visit(ast::AsgStmt* item) override;
    void visit(ast::CallExprStmt* item) override;
    void visit(ast::IfStmt* item) override;
    void visit(ast::ReturnStmt* item) override;

private:
    llvm::Function* create_module_initializer();
};

}  // namespace quirk