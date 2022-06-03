#pragma once

#include <memory>
#include <unordered_map>

#include "declaration.h"

namespace quirk::scopes {

class Scope {
    using Table = std::unordered_map<std::string_view, std::unique_ptr<Declaration>>;

public:
    class Iterator {
        Table::iterator it;

    public:
        Iterator(Table::iterator it) : it(it) {}

        Iterator operator++()
        {
            it++;
            return *this;
        }

        bool operator==(Iterator other) const { return it == other.it; }
        bool operator!=(Iterator other) const { return !(*this == other); }
        auto operator*() const { return it->second.get(); }
    };

private:
    Table decls;
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

    auto begin() { return Iterator(decls.begin()); }

    auto end() { return Iterator(decls.end()); }
};

} // namespace quirk::scopes