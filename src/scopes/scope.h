#pragma once

#include "declaration.h"
#include <memory>
#include <unordered_map>

namespace quirk::scopes {

class Scope {
    unordered_map<string_view, unique_ptr<Declaration>> decls;
    Scope* parent;

public:
    Scope(Scope&) = delete;
    Scope(Scope&&) = delete;

    Scope() : parent(nullptr) {}
    Scope(Scope* parent) : parent(parent) {}

    virtual ~Scope() {}

    bool add(unique_ptr<Declaration> decl)
    {
        auto [_, success] = decls.insert({decl->get_name(), move(decl)});
        return success;
    }

    Declaration* find(string name)
    {
        auto search = decls.find(name);
        if (search != decls.end()) {
            return search->second.get();
        }
        return nullptr;
    }
};

} // namespace quirk::scopes