#pragma once

#include <memory>
#include <unordered_map>

#include "declaration.h"

namespace quirk::scopes {

class Scope {
    std::unordered_map<std::string_view, std::unique_ptr<Declaration>> decls;
    Scope* parent;

public:
    Scope(Scope&) = delete;
    Scope(Scope&&) = delete;

    Scope() : parent(nullptr) {}
    Scope(Scope* parent) : parent(parent) {}

    virtual ~Scope() {}

    bool add(std::unique_ptr<Declaration> decl)
    {
        auto [_, success] = decls.insert({decl->get_name(), move(decl)});
        return success;
    }

    Declaration* find(std::string_view name)
    {
        auto search = decls.find(name);
        if (search != decls.end()) {
            return search->second.get();
        }
        return nullptr;
    }
};

} // namespace quirk::scopes