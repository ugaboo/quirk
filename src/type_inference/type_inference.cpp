// #include "type_inference.h"
// #include <assert.h>

// namespace quirk {

// void TypeInference::visit(ast::Function* node) {
//     type = node;
// }

// void TypeInference::visit(ast::Variable* node) {
//     if (node->get_def()->get_type_expr() != nullptr) {
//         node->get_def()->get_type_expr()->accept(this);
//     } else {
//         node->get_def()->get_rvalue()->accept(this);
//     }
// }

// void TypeInference::visit(ast::Parameter* node) {
//     node->get_def()->get_type()->accept(this);
// }

// void TypeInference::visit(ast::BinaryExpr* node) {
//     type = node->get_type();  // the type was set during scopes building
// }

// void TypeInference::visit(ast::CallExprStmt* node) {
//     TypeInference ti(node->get_designator());
//     auto func = dynamic_cast<ast::Function*>(ti.get_type());
//     if (func != nullptr) {
//         func->get_def()->get_ret_type_expr()->accept(this);
//     } else {
//         throw CompilationError::NotCallable;
//     }
// }

// void TypeInference::visit(ast::NameLiteral* node) {
//     node->get_decl()->accept(this);
// }

// void TypeInference::visit(ast::IntLiteral* node) {
//     type = ast::Int64Type::get_instance();
// }

// void TypeInference::visit(ast::ParameterDef* node) {
//     type = node->get_decl();
// }

// void TypeInference::visit(ast::Int64Type* node) {
//     type = node;
// }

// void TypeInference::visit(ast::Float64Type* node) {
//     type = node;
// }

// }  // namespace quirk