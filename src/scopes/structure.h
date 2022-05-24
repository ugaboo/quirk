#pragma once
#include "ast/struct_def_stmt.h"
#include "declaration.h"

namespace quirk::scopes {

using namespace ast;

class Structure : public Declaration {
    StructDefStmt* def;
    Scope          local_scope;

public:
    Structure(StructDefStmt* def) : def(def) {}

    string_view get_name() override { return def->get_name(); }

    auto get_def() { return def; }

    // auto count_local_decls() { return local_decls.size(); }
    // auto get_local_decl(size_t index) { return local_decls[index].get(); }
    // void add_local_decl(unique_ptr<Decl>& local) { local_decls.push_back(move(local)); }

    // void accept(Visitor* visitor) override;
};

}  // namespace quirk::scopes