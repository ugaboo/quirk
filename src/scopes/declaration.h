#pragma once

#include <map>
#include <memory>
#include <string>

namespace quirk::scopes {

using namespace std;

class Declaration {
public:
    virtual ~Declaration() {}
    virtual string_view get_name() = 0;
};

class Scope {
    unordered_map<string_view, unique_ptr<Declaration>> decls;

public:
    bool add(unique_ptr<Declaration> decl) {
        auto [_, success] = decls.insert({decl->get_name(), move(decl)});
        return success;
    }

    Declaration* find(string name) {
        auto search = decls.find(name);
        if (search != decls.end()) {
            return search->second.get();
        }
        return nullptr;
    }
};

}  // namespace quirk::scopes