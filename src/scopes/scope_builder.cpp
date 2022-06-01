#include "scope_builder.h"
#include "../compilation_error.h"

namespace quirk::scopes {

ScopeBuilder::ScopeBuilder(ast::TranslationUnit* unit, Scope& global_scope,
                           std::unordered_map<ast::NameLiteral*, Declaration*>& name_table)
    : root_node(unit), name_table(name_table)
{
    auto m = std::make_unique<Module>(unit, global_scope);
    local_scope = &m->get_scope();
    global_scope.insert(move(m));
}

ScopeBuilder::ScopeBuilder(ast::Node* root_node, Scope* local_scope,
                           std::unordered_map<ast::NameLiteral*, Declaration*>& name_table)
    : root_node(root_node), local_scope(local_scope), name_table(name_table)
{
}

void ScopeBuilder::process()
{
    root_node->accept(this);

    for (auto& b : future_work) {
        b.process();
    }
}

void ScopeBuilder::visit(ast::AsgStmt* node)
{
    if (node->get_rvalue() != nullptr) {
        node->get_rvalue()->accept(this);
    }
    if (node->get_type_expr() != nullptr) {
        node->get_type_expr()->accept(this);
    }
    // lvalue goes last to prevent incorrect handling of cases such as `a = a + 1`
    auto name = dynamic_cast<ast::NameLiteral*>(node->get_lvalue());
    if (name == nullptr) {
        node->get_lvalue()->accept(this);
        return;
    }
    auto decl = local_scope->lookup(name->get_value());
    if (decl != nullptr) {
        name_table.insert({name, decl});
        return;
    }
    // not found
    auto var = std::make_unique<Variable>(node);
    name_table.insert({name, var.get()});
    local_scope->insert(move(var));
}

void ScopeBuilder::visit(ast::FieldDefStmt* node)
{
    auto field = std::make_unique<Field>(node);
    name_table.insert({node->get_name(), field.get()});

    if (!local_scope->insert(move(field))) {
        throw CompilationError::Redefinition;
    }
}

void ScopeBuilder::visit(ast::FuncDefStmt* node)
{
    if (node == root_node) {
        Visitor::visit(node);
        return;
    }

    auto f = std::make_unique<Function>(node, *local_scope);
    name_table.insert({node->get_name(), f.get()});

    future_work.push_back(ScopeBuilder(node, &f->get_scope(), name_table));

    if (!local_scope->insert(move(f))) {
        throw CompilationError::Redefinition;
    }
}

void ScopeBuilder::visit(ast::NameLiteral* node)
{
    auto decl = local_scope->lookup(node->get_value());
    if (decl == nullptr) {
        throw CompilationError::ItemNotFound;
    }
    name_table.insert({node, decl});
}

void ScopeBuilder::visit(ast::ParamDefExpr* node)
{
    auto param = std::make_unique<Parameter>(node);
    name_table.insert({node->get_name(), param.get()});
    if (!local_scope->insert(move(param))) {
        throw CompilationError::Redefinition;
    }

    node->get_type()->accept(this);
}

void ScopeBuilder::visit(ast::StructDefStmt* node)
{
    if (node == root_node) {
        Visitor::visit(node);
        return;
    }

    auto s = std::make_unique<Structure>(node, *local_scope);
    name_table.insert({node->get_name(), s.get()});

    future_work.push_back(ScopeBuilder(node, &s->get_scope(), name_table));

    if (!local_scope->insert(move(s))) {
        throw CompilationError::Redefinition;
    }
}

} // namespace quirk::scopes
