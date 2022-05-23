// #include "exprgen.h"
// #include "namegen.h"
// #include "type_converter_llvm.h"
// #include "type_inference.h"

// #include "llvm/ADT/APFloat.h"
// #include "llvm/IR/Constants.h"

// namespace quirk {

// using std::string;

// void ExprGen::visit(ast::Function* node) {
//     value = decls.get_value(node);
// }

// void ExprGen::visit(ast::Variable* node) {
//     TypeInference ti(node);
//     TypeConverterLLVM conv(context, ti.get_type());
//     value = builder.CreateLoad(conv.get_type(), decls.get_value(node), string(node->get_name()));
// }

// void ExprGen::visit(ast::Parameter* node) {
//     value = decls.get_value(node);
// }

// void ExprGen::visit(ast::CallExprStmt* node) {
//     ExprGen gen(decls, node->get_designator());
//     auto designator = gen.get_value();

//     vector<llvm::Value*> args;
//     for (size_t i = 0; i < node->count_args(); i++) {
//         ExprGen gen(decls, node->get_arg(i));
//         args.push_back(gen.get_value());
//     }

//     TypeInference ti(node->get_designator());
//     TypeConverterLLVM conv(context, ti.get_type());
//     auto desig_llvm = conv.get_type();
//     auto func_type = static_cast<llvm::FunctionType*>(desig_llvm);
//     value = builder.CreateCall(func_type, designator, args);
// }

// void ExprGen::visit(ast::BinaryExpr* node) {
//     ExprGen gen_l(decls, node->get_left());
//     ExprGen gen_r(decls, node->get_right());
//     auto left = gen_l.get_value();
//     auto right = gen_r.get_value();

//     // value = builder.CreateCall(func_type, designator, args);

//     switch (node->get_kind()) {
//     case ast::BinaryExpr::Kind::Add:
//         value = builder.CreateAdd(left, right, "add");
//         break;
//     case ast::BinaryExpr::Kind::Sub:
//         value = builder.CreateSub(left, right, "sub");
//         break;
//     case ast::BinaryExpr::Kind::Mul:
//         value = builder.CreateMul(left, right, "mul");
//         break;
//     case ast::BinaryExpr::Kind::Div:
//         value = builder.CreateFDiv(left, right, "div");
//         break;
//     case ast::BinaryExpr::Kind::IntDiv: {
//         auto conv = builder.CreateFPToSI(right, builder.getInt64Ty());
//         value = builder.CreateSDiv(left, conv, "idiv");
//     } break;
//     case ast::BinaryExpr::Kind::Equal:
//         value = builder.CreateICmpEQ(left, right, "icmp");
//         break;
//     default:
//         throw std::logic_error("Not implemented");
//         break;
//     }
// }

// void ExprGen::visit(ast::NameLiteral* node) {
//     node->get_decl()->accept(this);
// }

// void ExprGen::visit(ast::IntLiteral* node) {
//     value = builder.getInt64(node->get_value());
// }

// void ExprGen::visit(ast::FloatLiteral* node) {
//     value = llvm::ConstantFP::get(context, llvm::APFloat(node->get_value()));
// }

// }  // namespace quirk