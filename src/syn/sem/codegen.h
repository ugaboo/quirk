#pragma once
#include "declgen.h"
#include "visitor.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

namespace quirk {

using std::map;
using std::string;
using std::string_view;
using std::unique_ptr;

// CodeGen generates llvm code for the module, functions and statements
class CodeGen : public Visitor {
    string filename;

    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;

    unique_ptr<llvm::Module> module;

    unique_ptr<DeclGen> decls;

    llvm::Value* llvm_value;

public:
    CodeGen(string filename);

    void visit(ast::Module* node) override;
    void visit(ast::FuncDefStmt* node) override;
    void visit(ast::AsgStmt* node) override;
    void visit(ast::CallExprStmt* node) override;
    void visit(ast::IfStmt* node) override;
    void visit(ast::ReturnStmt* node) override;

private:
    llvm::Function* create_module_initializer();
};

}  // namespace quirk