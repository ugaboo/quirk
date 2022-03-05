#include "exprgen.h"
#include "namegen.h"
#include "type_converter_llvm.h"
#include "type_inference.h"

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Constants.h"

namespace quirk {

using std::string;

void ExprGen::visit(ast::Function* item) {
    value = decls.get_value(item);
}

void ExprGen::visit(ast::Variable* item) {
    TypeInference ti(item);
    TypeConverterLLVM conv(context, ti.get_type());
    value = builder.CreateLoad(conv.get_type(), decls.get_value(item), string(item->get_name()));
}

void ExprGen::visit(ast::Parameter* item) {
    value = decls.get_value(item);
}

void ExprGen::visit(ast::CallExprStmt* item) {
    ExprGen gen(decls, item->get_designator());
    auto designator = gen.get_value();

    vector<llvm::Value*> args;
    for (size_t i = 0; i < item->count_args(); i++) {
        ExprGen gen(decls, item->get_arg(i));
        args.push_back(gen.get_value());
    }

    TypeInference ti(item->get_designator());
    TypeConverterLLVM conv(context, ti.get_type());
    auto desig_llvm = conv.get_type();
    auto func_type = static_cast<llvm::FunctionType*>(desig_llvm);
    value = builder.CreateCall(func_type, designator, args);
}

void ExprGen::visit(ast::BinaryExpr* item) {
    ExprGen gen_l(decls, item->get_left());
    ExprGen gen_r(decls, item->get_right());
    auto left = gen_l.get_value();
    auto right = gen_r.get_value();

    // value = builder.CreateCall(func_type, designator, args);

    switch (item->get_kind()) {
    case ast::BinaryExpr::Kind::Add:
        value = builder.CreateAdd(left, right, "add");
        break;
    case ast::BinaryExpr::Kind::Sub:
        value = builder.CreateSub(left, right, "sub");
        break;
    case ast::BinaryExpr::Kind::Mul:
        value = builder.CreateMul(left, right, "mul");
        break;
    case ast::BinaryExpr::Kind::Div:
        value = builder.CreateFDiv(left, right, "div");
        break;
    case ast::BinaryExpr::Kind::IntDiv: {
        auto conv = builder.CreateFPToSI(right, builder.getInt64Ty());
        value = builder.CreateSDiv(left, conv, "idiv");
    } break;
    case ast::BinaryExpr::Kind::Equal:
        value = builder.CreateICmpEQ(left, right, "icmp");
        break;
    default:
        throw std::logic_error("Not implemented");
        break;
    }
}

void ExprGen::visit(ast::NameLiteral* item) {
    item->get_decl()->accept(this);
}

void ExprGen::visit(ast::IntLiteral* item) {
    value = builder.getInt64(item->get_value());
}

void ExprGen::visit(ast::FloatLiteral* item) {
    value = llvm::ConstantFP::get(context, llvm::APFloat(item->get_value()));
}

}  // namespace quirk