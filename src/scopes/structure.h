#pragma once
#include <unordered_map>
#include "ast/struct_def_stmt.h"

namespace quirk::scopes {

class Structure : public Decl {
    StructDefStmt* def;
    vector<unique_ptr<Decl>> local_decls;

public:
    Structure(StructDefStmt* def) : def(def) {}

    auto get_name() { return def->get_name(); }
    auto get_def() { return def; }
    auto count_local_decls() { return local_decls.size(); }
    auto get_local_decl(size_t index) { return local_decls[index].get(); }
    void add_local_decl(unique_ptr<Decl>& local) { local_decls.push_back(move(local)); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast