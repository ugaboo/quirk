#include "visitor.h"

namespace quirk::scopes {

void Visitor::visit(BasicType* decl) {}

void Visitor::visit(Field* decl) {}

void Visitor::visit(Function* f)
{
    for (auto decl : f->get_scope()) {
        decl->accept(this);
    }
}

void Visitor::visit(Module* m)
{
    for (auto decl : m->get_scope()) {
        decl->accept(this);
    }
}

void Visitor::visit(Parameter* decl) {}

void Visitor::visit(Structure* s)
{
    for (auto decl : s->get_scope()) {
        decl->accept(this);
    }
}

void Visitor::visit(Variable* decl) {}

} // namespace quirk::scopes