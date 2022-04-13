#pragma once
#include <unordered_map>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "visitor.h"

namespace quirk {

using std::unordered_map;

// DeclGen generates and stores llvm code for declarations
class DeclGen : public Visitor {
    llvm::LLVMContext& context;
    llvm::IRBuilder<>& builder;
    llvm::Module* module;

    unordered_map<ast::Decl*, llvm::Value*> decls;

public:
    DeclGen(llvm::IRBuilder<>& builder, llvm::Module* module)
        : builder(builder), module(module), context(module->getContext()) {}

    auto get_value(ast::Decl* node) { return decls[node]; }
    auto& get_context() { return context; }
    auto& get_builder() { return builder; }

    void visit(ast::Function* node) override;
    void visit(ast::Variable* node) override;
};

}  // namespace quirk