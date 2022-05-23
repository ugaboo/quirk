// #pragma once
// #include "llvm/IR/LLVMContext.h"
// #include "type_inference.h"
// #include "visitor.h"

// namespace quirk {

// using std::vector;

// // TypeConverterLLVM is a helper visitor that converts ast::Decl into llvm::Type
// class TypeConverterLLVM : public Visitor {
//     llvm::LLVMContext& context;
//     llvm::Type* type = nullptr;

// public:
//     TypeConverterLLVM(llvm::LLVMContext& context, ast::Decl* node) : context(context) {
//         node->accept(this);
//         assert(type != nullptr);
//     }

//     auto get_type() { return type; }

//     void visit(ast::Function* node) override {
//         auto def = node->get_def();

//         vector<llvm::Type*> param_types;
//         param_types.reserve(def->count_params());
//         for (size_t i = 0; i < def->count_params(); i++) {
//             TypeInference ti(def->get_param(i)->get_type());
//             TypeConverterLLVM conv(context, ti.get_type());
//             param_types.push_back(conv.get_type());
//         }

//         llvm::Type* ret_type;
//         if (def->get_ret_type_expr() != nullptr) {
//             TypeInference ti(def->get_ret_type_expr());
//             TypeConverterLLVM conv(context, ti.get_type());
//             ret_type = conv.get_type();
//         } else {
//             ret_type = llvm::Type::getVoidTy(context);
//         }

//         type = llvm::FunctionType::get(ret_type, param_types, false);
//     }

//     void visit(ast::Int64Type* node) override { type = llvm::Type::getInt64Ty(context); }

//     void visit(ast::Float64Type* node) override { type = llvm::Type::getDoubleTy(context); }
// };

// }  // namespace quirk