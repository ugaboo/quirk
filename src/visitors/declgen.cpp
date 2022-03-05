#include "declgen.h"
#include "type_converter_llvm.h"

#include "llvm/ADT/Optional.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"

namespace quirk {

using std::make_unique;
using std::string;
using std::vector;

void DeclGen::visit(ast::Function* item) {
    TypeConverterLLVM conv(context, item);
    auto func_type = static_cast<llvm::FunctionType*>(conv.get_type());
    auto func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, string(item->get_name()), module);

    llvm::BasicBlock::Create(context, "", func);

    decls[item] = func;

    auto def = item->get_def();
    size_t i = 0;
    for (auto& arg : func->args()) {
        decls[def->get_param(i)->get_decl()] = &arg;
        i++;
    }
}

void DeclGen::visit(ast::Variable* item) {
    TypeInference ti(item);
    TypeConverterLLVM conv(context, ti.get_type());
    if (item->is_global()) {
        module->getOrInsertGlobal(string(item->get_name()), conv.get_type());
        auto var = module->getNamedGlobal(string(item->get_name()));
        var->setLinkage(llvm::GlobalValue::CommonLinkage);
        // var->setInitializer(llvm::ConstantInt(tf.get_type(), llvm::APInt(0));
        var->setInitializer(llvm::Constant::getNullValue(conv.get_type()));
        decls[item] = var;
    } else {
        decls[item] = builder.CreateAlloca(conv.get_type());
    }
}

}  // namespace quirk