#include "scope_builder.h"
#include <cassert>
#include "namegen.h"
#include "type_inference.h"

namespace quirk {

using std::make_unique;

ast::Decl* ScopeBuilder::Find(string_view name) {
    for (auto it = name_tables.rbegin(); it != name_tables.rend(); it++) {
        auto search = it->find(string(name));
        if (search != it->end()) {
            return search->second;
        }
    }
    return nullptr;
}

void ScopeBuilder::visit(ast::AsgStmt* node) {
    if (node->get_type_expr() != nullptr) {
        node->get_type_expr()->accept(this);
    }
    if (node->get_rvalue() != nullptr) {
        node->get_rvalue()->accept(this);
    }
    // lvalue goes last to prevent incorrect handling of cases such as a=a+1
    auto name = dynamic_cast<ast::NameLiteral*>(node->get_lvalue());
    if (name != nullptr) {
        name->set_decl(Find(name->get_value()));
        if (name->get_decl() == nullptr) {
            auto var = make_unique<ast::Variable>(node);
            if (name_tables.size() == 1) {  // module level
                var->make_global();
            }
            name->set_decl(var.get());
            name_tables.back().insert_or_assign(string(name->get_value()), var.get());
            local_decls.back().push_back(move(var));
        }
    } else {
        node->get_lvalue()->accept(this);
    }
}

void ScopeBuilder::visit(ast::BinaryExpr* node) {
    node->get_left()->accept(this);
    node->get_right()->accept(this);

    NameGen op_func_name(node);

    auto decl = dynamic_cast<ast::OpFunc*>(Find(op_func_name.get_name()));
    if (decl != nullptr) {
        node->set_type(decl->get_ret_type());
    } else {
        throw CompilationError::ItemNotFound;
    }
}

void ScopeBuilder::visit(ast::FieldDef* node) {
    auto field = make_unique<ast::Field>(node);
    node->set_decl(field.get());
    auto [_, success] = name_tables.back().insert({string(node->get_name()), field.get()});
    if (!success) {
        throw CompilationError::Redefinition;
    }
    local_decls.back().push_back(move(field));
}

void ScopeBuilder::visit(ast::CallExprStmt* node) {
    node->get_designator()->accept(this);
    for (size_t i = 0; i < node->count_args(); i++) {
        node->get_arg(i)->accept(this);
    }
}

void ScopeBuilder::visit(ast::FuncDefStmt* node) {
    auto func = make_unique<ast::Function>(node);
    node->set_decl(func.get());
    functions.push_back(func.get());
    auto [_, success] = name_tables.back().insert({string(node->get_name()), func.get()});
    if (!success) {
        throw CompilationError::Redefinition;
    }
    local_decls.back().push_back(move(func));
}

void ScopeBuilder::visit(ast::IfStmt* node) {
    for (size_t i = 0; i < node->count_branches(); i++) {
        node->get_condition(i)->accept(this);
        for (size_t j = 0; j < node->count_branch_stmts(i); j++) {
            node->get_branch_stmt(i, j)->accept(this);
        }
    }
    for (size_t i = 0; i < node->count_else_stmts(); i++) {
        node->get_else_stmt(i)->accept(this);
    }
}

void ScopeBuilder::visit(ast::ListLiteral* node) {
    for (size_t i = 0; i < node->count_exprs(); i++) {
        node->get_expr(i)->accept(this);
    }
}

void ScopeBuilder::visit(ast::MemberAccessExpr* node) {
    node->get_designator()->accept(this);
    node->get_selector()->accept(this);
}

void ScopeBuilder::visit(ast::NameLiteral* node) {
    auto decl = Find(node->get_value());
    if (decl != nullptr) {
        node->set_decl(decl);
    } else {
        throw CompilationError::ItemNotFound;
    }
}

void ScopeBuilder::visit(ast::ReturnStmt* node) {
    if (node->get_expr() != nullptr) {
        node->get_expr()->accept(this);
    }
}

void ScopeBuilder::visit(ast::StructDefStmt* node) {
    auto st = make_unique<ast::Structure>(node);
    node->set_decl(st.get());
    structures.push_back(st.get());
    auto [_, success] = name_tables.back().insert({string(node->get_name()), st.get()});
    if (!success) {
        throw CompilationError::Redefinition;
    }
    local_decls.back().push_back(move(st));
}

void ScopeBuilder::visit(ast::SubscriptExpr* node) {
    node->get_designator()->accept(this);
    for (size_t i = 0; i < node->count_keys(); i++) {
        node->get_key(i)->accept(this);
    }
}

void ScopeBuilder::visit(ast::UnaryExpr* node) {
    node->get_expr()->accept(this);
}

void ScopeBuilder::visit(ast::ParameterDef* node) {
    auto param = make_unique<ast::Parameter>(node);
    node->set_decl(param.get());
    auto [_, success] = name_tables.back().insert({string(param->get_name()), param.get()});
    if (!success) {
        throw CompilationError::Redefinition;
    }
    local_decls.back().push_back(move(param));
    node->get_type()->accept(this);
}

void ScopeBuilder::visit(ast::WhileStmt* node) {
    node->get_condition()->accept(this);
    for (size_t i = 0; i < node->count_stmts(); i++) {
        node->get_stmt(i)->accept(this);
    }
}

void ScopeBuilder::visit(ast::Module* node) {
    name_tables.emplace_back();
    local_decls.emplace_back();
    add_primitive_types();
    add_operator_funcs();
    for (size_t i = 0; i < node->count_stmts(); i++) {
        node->get_stmt(i)->accept(this);
    }
    for (auto func : functions) {
        func->accept(this);
    }
    for (auto st : structures) {
        st->accept(this);
    }
    for (auto& decl : local_decls.back()) {
        node->add_local_decl(decl);
    }
    local_decls.pop_back();
    name_tables.pop_back();

    assert(local_decls.empty());
    assert(name_tables.empty());
}

void ScopeBuilder::visit(ast::Function* node) {
    auto def = node->get_def();
    name_tables.emplace_back();
    local_decls.emplace_back();
    for (size_t i = 0; i < def->count_params(); i++) {
        def->get_param(i)->accept(this);
    }
    if (def->get_ret_type_expr() != nullptr) {
        def->get_ret_type_expr()->accept(this);
    }
    for (size_t i = 0; i < def->count_stmts(); i++) {
        def->get_stmt(i)->accept(this);
    }
    for (auto& decl : local_decls.back()) {
        node->add_local_decl(decl);
    }
    local_decls.pop_back();
    name_tables.pop_back();
}

void ScopeBuilder::visit(ast::Structure* node) {
    auto def = node->get_def();
    name_tables.emplace_back();
    local_decls.emplace_back();
    for (size_t i = 0; i < def->count_fields(); i++) {
        def->get_field(i)->accept(this);
    }
    for (auto& decl : local_decls.back()) {
        node->add_local_decl(decl);
    }
    local_decls.pop_back();
    name_tables.pop_back();
}

void ScopeBuilder::add_primitive_types() {
    auto& table = name_tables.front();
    table["Int"] = ast::Int64Type::get_instance();
    table["Float"] = ast::Float64Type::get_instance();
}

void ScopeBuilder::add_bin_op(string name, ast::Decl* left_type, ast::Decl* right_type, ast::Decl* ret_type) {
    auto func = make_unique<ast::OpFunc>(name, left_type, right_type, ret_type);
    NameGen gen(func.get());
    name_tables.front().insert_or_assign(gen.get_name(), func.get());
    local_decls.front().push_back(move(func));
}

void ScopeBuilder::add_operator_funcs() {
    auto i64 = ast::Int64Type::get_instance();
    auto f64 = ast::Float64Type::get_instance();
    add_bin_op("__add__", i64, i64, i64);
    add_bin_op("__add__", f64, i64, f64);
    add_bin_op("__add__", i64, f64, f64);
    add_bin_op("__add__", f64, f64, f64);
}

}  // namespace quirk
