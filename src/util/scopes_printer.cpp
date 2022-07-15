#include "scopes_printer.h"
#include "indent_guard.h"

namespace quirk::util {

ScopesPrinter::ScopesPrinter(std::ostream& out, scopes::Module* mod) : out(out)
{
    visit(mod);
}

void ScopesPrinter::visit(scopes::Module* m)
{
    for (auto [name, decl] : m->get_scope()) {
        fmt::print(out, "{}'{}': ", offset(indent), name);
        decl->accept(this);
    }
}

void ScopesPrinter::visit(scopes::BasicType* decl)
{
    fmt::print(out, "BasicType\n");
}

void ScopesPrinter::visit(scopes::Field* decl)
{
    fmt::print(out, "Field\n");
}

void ScopesPrinter::visit(scopes::Function* f)
{
    fmt::print(out, "Function\n");

    IndentGuard inc(indent);
    for (auto [name, decl] : f->get_scope()) {
        fmt::print(out, "{}'{}': ", offset(indent), name);
        decl->accept(this);
    }
}

void ScopesPrinter::visit(scopes::Parameter* decl)
{
    fmt::print(out, "Parameter\n", offset(indent), "");
}

void ScopesPrinter::visit(scopes::Structure* s)
{
    fmt::print(out, "Structure\n", offset(indent), "");

    IndentGuard inc(indent);
    for (auto [name, decl] : s->get_scope()) {
        fmt::print(out, "{}'{}': ", offset(indent), name);
        decl->accept(this);
    }
}

void ScopesPrinter::visit(scopes::Variable* decl)
{
    fmt::print(out, "Variable\n");
}

} // namespace quirk::util