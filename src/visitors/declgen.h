#pragma once
#include <unordered_map>
#include "ast/visitor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

namespace quirk {

using std::unordered_map;

// DeclGen generates and stores llvm code for declarations
class DeclGen : public ast::Visitor {
    llvm::LLVMContext& context;
    llvm::IRBuilder<>& builder;
    llvm::Module* module;

    unordered_map<ast::Decl*, llvm::Value*> decls;

public:
    DeclGen(llvm::IRBuilder<>& builder, llvm::Module* module)
        : builder(builder), module(module), context(module->getContext()) {}

    auto get_value(ast::Decl* item) { return decls[item]; }
    auto& get_context() { return context; }
    auto& get_builder() { return builder; }

    void visit(ast::Function* item) override;
    void visit(ast::Variable* item) override;
};

}  // namespace quirk