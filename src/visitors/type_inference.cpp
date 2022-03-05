#include "type_inference.h"
#include <assert.h>

namespace quirk {

void TypeInference::visit(ast::Function* item) {
    type = item;
}

void TypeInference::visit(ast::Variable* item) {
    if (item->get_def()->get_type_expr() != nullptr) {
        item->get_def()->get_type_expr()->accept(this);
    } else {
        item->get_def()->get_rvalue()->accept(this);
    }
}

void TypeInference::visit(ast::Parameter* item) {
    item->get_def()->get_type()->accept(this);
}

void TypeInference::visit(ast::BinaryExpr* item) {
    type = item->get_type();  // the type was set during scopes building
}

void TypeInference::visit(ast::CallExprStmt* item) {
    TypeInference ti(item->get_designator());
    auto func = dynamic_cast<ast::Function*>(ti.get_type());
    if (func != nullptr) {
        func->get_def()->get_ret_type_expr()->accept(this);
    } else {
        throw CompilationError::NotCallable;
    }
}

void TypeInference::visit(ast::NameLiteral* item) {
    item->get_decl()->accept(this);
}

void TypeInference::visit(ast::IntLiteral* item) {
    type = ast::Int64Type::get_instance();
}

void TypeInference::visit(ast::ParameterDef* item) {
    type = item->get_decl();
}

void TypeInference::visit(ast::Int64Type* item) {
    type = item;
}

void TypeInference::visit(ast::Float64Type* item) {
    type = item;
}

}  // namespace quirk