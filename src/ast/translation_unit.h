#pragma once

#include <memory>
#include <string>
#include <vector>

#include "node.h"

namespace quirk::ast {

class TranslationUnit : public Node {
    std::string filename;
    util::PtrList<Stmt> stmts;

public:
    TranslationUnit(std::string filename, std::vector<std::unique_ptr<Stmt>>& stmts)
        : Node(Context{}), filename(filename)
    {
        for (auto& s : stmts) {
            TranslationUnit::stmts.push_back(move(s));
        }
    }

    auto get_filename() { return std::string_view(filename); }

    auto& get_stmts() { return stmts; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast