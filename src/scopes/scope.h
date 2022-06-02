#pragma once

#include <memory>
#include <unordered_map>

#include "../util/ptr_iterator.h"
#include "declaration.h"

namespace quirk::scopes {

class Scope {
    std::unordered_map<std::string_view, std::unique_ptr<Declaration>> decls;
    Scope* parent;

public:
    Scope() : parent(nullptr) {}
    Scope(Scope& parent) : parent(&parent) {}

    virtual ~Scope() {}

    bool insert(std::unique_ptr<Declaration> decl)
    {
        auto [_, success] = decls.insert({decl->get_name(), move(decl)});
        return success;
    }

    Declaration* lookup(std::string_view name)
    {
        auto it = decls.find(name);
        if (it != decls.end()) {
            return it->second.get();
        }
        if (parent != nullptr) {
            return parent->lookup(name);
        }
        return nullptr;
    }

    auto begin() { return util::PtrIterator(decls.begin()); }

    auto end() { return util::PtrIterator(decls.end()); }
};

} // namespace quirk::scopes