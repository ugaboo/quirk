#pragma once
#include <unordered_map>
#include "ast/func_def_stmt.h"

namespace quirk::scopes {

class Function : public Decl {
    FuncDefStmt* def = nullptr;
    vector<unique_ptr<Decl>> local_decls;

public:
    Function(FuncDefStmt* def) : def(def) {}

    auto get_name() { return def->get_name(); }
    auto get_def() { return def; }
    auto count_local_decls() { return local_decls.size(); }
    auto get_local_decl(size_t index) { return local_decls[index].get(); }
    void add_local_decl(unique_ptr<Decl>& local) { local_decls.push_back(move(local)); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast