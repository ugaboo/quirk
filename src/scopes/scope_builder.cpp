#include "scope_builder.h"
#include <cassert>

namespace quirk::scopes {

ScopeBuilder::ScopeBuilder(ast::Node* node, Scope& scope,
                           std::unordered_map<ast::NameLiteral*, Declaration*>& bindings)
    : node(node), scope(scope), bindings(bindings)
{
}

void ScopeBuilder::process()
{
    node->accept(this);

    for (auto& b : builders) {
        b->process();
    }
}

void ScopeBuilder::visit(ast::AsgStmt* node)
{
    if (node->get_type_expr() != nullptr) {
        node->get_type_expr()->accept(this);
    }
    if (node->get_rvalue() != nullptr) {
        node->get_rvalue()->accept(this);
    }
    // lvalue goes last to prevent incorrect handling of cases such as `a = a + 1`
    auto name = dynamic_cast<ast::NameLiteral*>(node->get_lvalue());
    if (name == nullptr) {
        node->get_lvalue()->accept(this);
        return;
    }
    auto decl = scope.find(name->get_value());
    if (decl == nullptr) {
        auto var = std::make_unique<Variable>(node);
        // if (scopes.size() == 1) { // module level
        //     var->make_global();
        // }
        bindings.insert({name, var.get()});
        scope.insert(move(var));
    } else {
        bindings.insert({name, decl});
    }
}

void ScopeBuilder::visit(ast::FieldDefStmt* node)
{
    auto field = std::make_unique<Field>(node);
    bindings.insert({node->get_name(), field.get()});
    scope.insert(move(field));
}

void ScopeBuilder::visit(ast::FuncDefStmt* node)
{
    if (node == ScopeBuilder::node) {
        Visitor::visit(node);
        return;
    }

    auto func = std::make_unique<Function>(node, scope);
    bindings.insert({node->get_name(), func.get()});
    auto builder = std::make_unique<ScopeBuilder>(node, func->get_scope(), bindings);
    builders.push_back(move(builder));
    scope.insert(move(func));
}

void ScopeBuilder::visit(ast::NameLiteral* node)
{
    auto decl = scope.find(node->get_value());
    if (decl == nullptr) {
        throw CompilationError::ItemNotFound;
    }
    bindings.insert({node, decl});
}

void ScopeBuilder::visit(ast::ParamDefExpr* node)
{
    auto param = std::make_unique<Parameter>(node);
    bindings.insert({node->get_name(), param.get()});
    scope.insert(move(param));

    node->get_type()->accept(this);
}

void ScopeBuilder::visit(ast::StructDefStmt* node)
{
    if (node == ScopeBuilder::node) {
        Visitor::visit(node);
        return;
    }

    auto st = std::make_unique<Structure>(node, scope);
    bindings.insert({node->get_name(), st.get()});
    auto builder = std::make_unique<ScopeBuilder>(node, st->get_scope(), bindings);
    builders.push_back(move(builder));
    scope.insert(move(st));
}

void ScopeBuilder::visit(ast::TranslationUnit* node)
{
    auto mod = std::make_unique<Module>(node, scope);
    scope.insert(move(mod));

    Visitor::visit(node);
}

// void ScopeBuilder::visit(ast::Module* node) {
//     name_tables.emplace_back();
//     local_decls.emplace_back();
//     add_primitive_types();
//     add_operator_funcs();
//     for (size_t i = 0; i < node->count_stmts(); i++) {
//         node->get_stmt(i)->accept(this);
//     }
//     for (auto func : functions) {
//         func->accept(this);
//     }
//     for (auto st : structures) {
//         st->accept(this);
//     }
//     for (auto& decl : local_decls.back()) {
//         node->add_local_decl(decl);
//     }
//     local_decls.pop_back();
//     name_tables.pop_back();

//     assert(local_decls.empty());
//     assert(name_tables.empty());
// }

// void ScopeBuilder::visit(ast::Function* node) {
//     auto def = node->get_def();
//     name_tables.emplace_back();
//     local_decls.emplace_back();
//     for (size_t i = 0; i < def->count_params(); i++) {
//         def->get_param(i)->accept(this);
//     }
//     if (def->get_ret_type_expr() != nullptr) {
//         def->get_ret_type_expr()->accept(this);
//     }
//     for (size_t i = 0; i < def->count_stmts(); i++) {
//         def->get_stmt(i)->accept(this);
//     }
//     for (auto& decl : local_decls.back()) {
//         node->add_local_decl(decl);
//     }
//     local_decls.pop_back();
//     name_tables.pop_back();
// }

// void ScopeBuilder::visit(ast::Structure* node) {
//     auto def = node->get_def();
//     name_tables.emplace_back();
//     local_decls.emplace_back();
//     for (size_t i = 0; i < def->count_fields(); i++) {
//         def->get_field(i)->accept(this);
//     }
//     for (auto& decl : local_decls.back()) {
//         node->add_local_decl(decl);
//     }
//     local_decls.pop_back();
//     name_tables.pop_back();
// }

// void ScopeBuilder::add_primitive_types() {
//     auto& table = name_tables.front();
//     table["Int"] = ast::Int64Type::get_instance();
//     table["Float"] = ast::Float64Type::get_instance();
// }

// void ScopeBuilder::add_bin_op(string name, ast::Decl* left_type, ast::Decl* right_type,
// ast::Decl* ret_type) {
//     auto func = make_unique<ast::OpFunc>(name, left_type, right_type, ret_type);
//     NameGen gen(func.get());
//     name_tables.front().insert_or_assign(gen.get_name(), func.get());
//     local_decls.front().push_back(move(func));
// }

// void ScopeBuilder::add_operator_funcs() {
//     auto i64 = ast::Int64Type::get_instance();
//     auto f64 = ast::Float64Type::get_instance();
//     add_bin_op("__add__", i64, i64, i64);
//     add_bin_op("__add__", f64, i64, f64);
//     add_bin_op("__add__", i64, f64, f64);
//     add_bin_op("__add__", f64, f64, f64);
// }

} // namespace quirk::scopes
