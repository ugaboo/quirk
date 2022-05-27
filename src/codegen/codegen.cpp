// #include "codegen.h"
// #include "exprgen.h"
// #include "fmt/core.h"

// #include "llvm/ADT/Optional.h"
// #include "llvm/Support/FileSystem.h"
// #include "llvm/Support/Host.h"
// #include "llvm/Support/TargetSelect.h"
// #include "llvm/Support/raw_ostream.h"
// #include "llvm/Target/TargetMachine.h"
// #include "llvm/Target/TargetOptions.h"

// namespace quirk {

// using std::make_unique;
// using std::std::vector;

// CodeGen::CodeGen(string filename) : filename(filename), builder(context) {}

// void CodeGen::visit(ast::Module* node) {
//     module = make_unique<llvm::Module>("module", context);
//     auto init_func = create_module_initializer();

//     decls = make_unique<DeclGen>(builder, module.get());
//     for (size_t i = 0; i < node->count_local_decls(); i++) {
//         node->get_local_decl(i)->accept(decls.get());
//     }

//     for (size_t i = 0; i < node->count_stmts(); i++) {
//         node->get_stmt(i)->accept(this);
//     }

//     builder.CreateRet(builder.getInt32(0));

//     std::error_code err;
//     llvm::raw_fd_ostream out(filename, err, llvm::sys::fs::OF_None);
//     module->print(out, nullptr);
// }

// void CodeGen::visit(ast::FuncDefStmt* node) {
//     auto func = static_cast<llvm::Function*>(decls->get_value(node->get_decl()));
//     // func->addFnAttr(llvm::Attribute::AlwaysInline);

//     size_t i = 0;
//     for (auto& arg : func->args()) {
//         arg.setName(string(node->get_param(i)->get_name()));
//         i++;
//     }

//     auto cur_block = builder.GetInsertBlock();
//     builder.SetInsertPoint(&func->back());

//     auto func_decl = node->get_decl();
//     for (size_t i = 0; i < func_decl->count_local_decls(); i++) {
//         func_decl->get_local_decl(i)->accept(this);
//     }
//     for (size_t i = 0; i < node->count_stmts(); i++) {
//         node->get_stmt(i)->accept(this);
//     }

//     if (node->get_ret_type_expr() == nullptr) {
//         builder.CreateRetVoid();
//     }

//     builder.SetInsertPoint(cur_block);
// }

// void CodeGen::visit(ast::AsgStmt* node) {
//     llvm::Value* lvalue;
//     auto name = dynamic_cast<ast::NameLiteral*>(node->get_lvalue());
//     if (name != nullptr) {
//         lvalue = decls->get_value(name->get_decl());
//     } else {
//         ExprGen gen(*decls, node->get_lvalue());
//         lvalue = gen.get_value();
//     }
//     ExprGen gen(*decls, node->get_rvalue());
//     auto rvalue = gen.get_value();
//     builder.CreateStore(rvalue, lvalue);
// }

// void CodeGen::visit(ast::CallExprStmt* node) {
//     ExprGen gen(*decls, static_cast<ast::Stmt*>(node));
// }

// void CodeGen::visit(ast::IfStmt* node) {
//     auto cur_block = builder.GetInsertBlock();
//     auto func = cur_block->getParent();

//     auto end_block = llvm::BasicBlock::Create(context, "end");

//     for (size_t i = 0; i < node->count_branches(); i++) {
//         ExprGen gen(*decls, node->get_condition(i));
//         auto condition = gen.get_value();

//         auto then_block = llvm::BasicBlock::Create(context, "then", func);
//         auto else_block = llvm::BasicBlock::Create(context, "else");
//         builder.CreateCondBr(condition, then_block, else_block);

//         builder.SetInsertPoint(then_block);
//         for (size_t j = 0; j < node->count_branch_stmts(i); j++) {
//             node->get_branch_stmt(i, j)->accept(this);
//         }
//         builder.CreateBr(end_block);

//         func->getBasicBlockList().push_back(else_block);
//         builder.SetInsertPoint(else_block);
//     }

//     for (size_t i = 0; i < node->count_else_stmts(); i++) {
//         node->get_else_stmt(i)->accept(this);
//     }
//     builder.CreateBr(end_block);

//     func->getBasicBlockList().push_back(end_block);
//     builder.SetInsertPoint(end_block);
// }

// void CodeGen::visit(ast::ReturnStmt* node) {
//     if (node->get_expr() != nullptr) {
//         ExprGen gen(*decls, node->get_expr());
//         auto expr = gen.get_value();
//         builder.CreateRet(expr);
//     } else {
//         builder.CreateRetVoid();
//     }
// }

// llvm::Function* CodeGen::create_module_initializer() {
//     auto funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
//     auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main",
//     module.get());

//     auto block = llvm::BasicBlock::Create(context, "", func);
//     builder.SetInsertPoint(block);

//     return func;
// }

// }  // namespace quirk