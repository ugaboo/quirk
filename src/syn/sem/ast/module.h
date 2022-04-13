#pragma once
#include <unordered_map>
#include "node.h"

namespace quirk::ast {

class Module {
    vector<unique_ptr<Stmt>> stmts;
    vector<unique_ptr<Decl>> local_decls;

public:
    Module(vector<unique_ptr<Stmt>>& stmts) {
        for (auto& stmt : stmts) {
            Module::stmts.push_back(move(stmt));
        }
    }

    auto count_stmts() { return stmts.size(); }
    auto get_stmt(size_t index) { return stmts[index].get(); }
    void add_local_decl(unique_ptr<Decl>& local) { local_decls.push_back(move(local)); }
    auto count_local_decls() { return local_decls.size(); }
    auto get_local_decl(size_t index) { return local_decls[index].get(); }
};

}  // namespace quirk::ast