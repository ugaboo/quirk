#pragma once

#include "fmt/ostream.h"

#include "../scopes/visitor.h"

namespace quirk::util {

class ScopesPrinter : scopes::Visitor {
    std::ostream& out;
    int indent = 0;

public:
    ScopesPrinter(std::ostream& out, scopes::Scope& global_scope);

    void visit(scopes::BasicType* decl) override;
    void visit(scopes::Field* decl) override;
    void visit(scopes::Function* decl) override;
    void visit(scopes::Module* decl) override;
    void visit(scopes::Parameter* decl) override;
    void visit(scopes::Structure* decl) override;
    void visit(scopes::Variable* decl) override;

private:
    template <typename S, typename... Args> void print(const S& format_str, Args&&... args)
    {
        for (auto i = 0; i < indent; i++) {
            fmt::print(out, "    ");
        }
        fmt::print(out, format_str, args...);
    }
};

} // namespace quirk::util
