#pragma once

#include <memory>
#include <unordered_map>

#include "prog_obj.h"

namespace quirk::scopes {

class Scope {
    using Table = std::unordered_map<std::string_view, std::unique_ptr<ProgObj>>;

public:
    class Iterator {
    public:
        Iterator(Table::iterator it) : it(it) {}

        Iterator operator++()
        {
            it++;
            return *this;
        }

        bool operator==(Iterator other) const { return it == other.it; }
        bool operator!=(Iterator other) const { return !(*this == other); }
        auto operator*() const { return std::make_pair(it->first, it->second.get()); }

    private:
        Table::iterator it;
    };

public:
    Scope() {}

    Scope(Scope& other) = delete;

    Scope(Scope&& other)
    {
        for (auto& [k, v] : other.items) {
            items[k] = move(v);
        }
        other.items.clear();
    }

    virtual ~Scope() {}

    bool insert(std::string_view name, std::unique_ptr<ProgObj> item)
    {
        auto [_, success] = items.insert({name, std::move(item)});
        return success;
    }

    ProgObj* find(std::string_view name) const
    {
        auto it = items.find(name);
        if (it != items.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    auto begin() { return Iterator(items.begin()); }

    auto end() { return Iterator(items.end()); }

private:
    Table items;
};

} // namespace quirk::scopes