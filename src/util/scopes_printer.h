#pragma once

#include "fmt/ostream.h"

#include "../scopes/visitor.h"

namespace quirk::util {

class ScopesPrinter : scopes::Visitor {
public:
    ScopesPrinter(std::ostream& out, scopes::Module* mod);

    void visit(scopes::Module* decl) override;

private:
    void visit(scopes::BasicType* decl) override;
    void visit(scopes::Field* decl) override;
    void visit(scopes::Function* decl) override;
    void visit(scopes::Parameter* decl) override;
    void visit(scopes::Structure* decl) override;
    void visit(scopes::Variable* decl) override;

private:
    std::ostream& out;
    uint64_t indent = 0;
};

} // namespace quirk::util
