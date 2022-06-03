#include "scopes_printer.h"
#include "indent_guard.h"

namespace quirk::util {

ScopesPrinter::ScopesPrinter(std::ostream& out, scopes::Scope& global_scope) : out(out)
{
    for (auto decl : global_scope) {
        decl->accept(this);
    }
}

void ScopesPrinter::visit(scopes::BasicType* decl)
{
    fmt::print(out, "{}{}: BasicType\n", offset(indent), decl->get_name());
}

void ScopesPrinter::visit(scopes::Field* decl)
{
    fmt::print(out, "{}{}: Field\n", offset(indent), decl->get_name());
}

void ScopesPrinter::visit(scopes::Function* decl)
{
    fmt::print(out, "{}{}: Function\n", offset(indent), decl->get_name());

    IndentGuard inc(indent);
    scopes::Visitor::visit(decl);
}

void ScopesPrinter::visit(scopes::Module* decl)
{
    fmt::print(out, "{}{}: Module\n", offset(indent), decl->get_name());

    IndentGuard inc(indent);
    scopes::Visitor::visit(decl);
}

void ScopesPrinter::visit(scopes::Parameter* decl)
{
    fmt::print(out, "{}{}: Parameter\n", offset(indent), decl->get_name());
}

void ScopesPrinter::visit(scopes::Structure* decl)
{
    fmt::print(out, "{}{}: Structure\n", offset(indent), decl->get_name());

    IndentGuard inc(indent);
    scopes::Visitor::visit(decl);
}

void ScopesPrinter::visit(scopes::Variable* decl)
{
    fmt::print(out, "{}{}: Variable\n", offset(indent), decl->get_name());
}

} // namespace quirk::util