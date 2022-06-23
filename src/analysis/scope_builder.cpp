#include "scope_builder.h"
#include "../builtins/magic_names.h"
#include "../builtins/reserved.h"
#include "../compilation_error.h"

namespace quirk::analysis {

std::unique_ptr<scopes::Module> ScopeBuilder::build(ast::TranslationUnit* node)
{
    Visitor::visit(node); // traverse statements and fill the scope
    return std::make_unique<scopes::Module>(std::move(scope));
}

std::unique_ptr<scopes::Function> ScopeBuilder::build(ast::FuncDefStmt* node)
{
    Visitor::visit(node);
    return std::make_unique<scopes::Function>(std::move(scope));
}

std::unique_ptr<scopes::Structure> ScopeBuilder::build(ast::StructDefStmt* node)
{
    Visitor::visit(node);
    return std::make_unique<scopes::Structure>(std::move(scope));
}

void ScopeBuilder::visit(ast::AsgStmt* node)
{
    auto lit = dynamic_cast<ast::NameLiteral*>(node->get_lvalue());
    if (lit == nullptr) {
        Visitor::visit(node);
        return;
    }
    auto name = check_name(lit);
    auto decl = scope.find(name);
    if (decl != nullptr) {
        Visitor::visit(node);
        return;
    }
    auto v = std::make_unique<scopes::Variable>();
    scope.insert(name, std::move(v));

    Visitor::visit(node);
}

// void ScopeBuilder::visit(ast::BinaryExpr* node)
// {
//     auto name = builtins::get_magic_name(node->get_kind());
//     if (name != "") {
//         auto decl = local_scope->lookup(name);
//         if (decl != nullptr) {
//             bindings.insert({node, decl});
//         }
//     }
//     Visitor::visit(node);
// }

void ScopeBuilder::visit(ast::FieldDefStmt* node)
{
    auto name = check_name(node->get_name());
    auto f = std::make_unique<scopes::Field>();
    if (!scope.insert(name, std::move(f))) {
        throw CompilationError::Redefinition;
    }
    Visitor::visit(node);
}

void ScopeBuilder::visit(ast::FuncDefStmt* node)
{
    auto name = check_name(node->get_name());
    ScopeBuilder sb;
    auto f = sb.build(node);
    auto success = scope.insert(name, std::move(f));
    if (!success) {
        throw CompilationError::Redefinition;
    }
}

// void ScopeBuilder::visit(ast::NameLiteral* node)
// {
//     auto decl = local_scope->lookup(node->get_value());
//     if (decl == nullptr) {
//         throw CompilationError::ItemNotFound;
//     }
//     bindings.insert({node, decl});
// }

void ScopeBuilder::visit(ast::ParamDefExpr* node)
{
    auto name = check_name(node->get_name());
    auto p = std::make_unique<scopes::Parameter>();
    if (!scope.insert(name, std::move(p))) {
        throw CompilationError::Redefinition;
    }
    Visitor::visit(node);
}

void ScopeBuilder::visit(ast::StructDefStmt* node)
{
    auto name = check_name(node->get_name());
    ScopeBuilder sb;
    auto f = sb.build(node);
    auto success = scope.insert(name, std::move(f));
    if (!success) {
        throw CompilationError::Redefinition;
    }
}

std::string_view ScopeBuilder::check_name(ast::NameLiteral* node)
{
    auto name = node->get_value();
    if (builtins::is_reserved(name)) {
        throw CompilationError::ReservedName;
    }
    return name;
}

// void ScopeBuilder::visit(ast::UnaryExpr* node)
// {
//     auto name = builtins::get_magic_name(node->get_kind());
//     if (name != "") {
//         auto decl = local_scope->lookup(name);
//         if (decl != nullptr) {
//             bindings.insert({node, decl});
//         }
//     }
//     Visitor::visit(node);
// }

} // namespace quirk::analysis
