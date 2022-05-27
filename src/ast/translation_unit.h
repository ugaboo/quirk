#pragma once

#include <memory>
#include <vector>

#include "node.h"

namespace quirk::ast {

class TranslationUnit {
    std::vector<std::unique_ptr<Stmt>> stmts;

public:
    TranslationUnit() = delete;
    TranslationUnit(TranslationUnit&) = delete;
    TranslationUnit(TranslationUnit&&) = delete;

    TranslationUnit(std::vector<std::unique_ptr<Stmt>>& stmts)
    {
        for (auto& s : stmts) {
            TranslationUnit::stmts.push_back(move(s));
        }
    }

    virtual ~TranslationUnit() {}

    auto count_stmts() { return stmts.size(); }
    auto get_stmt(size_t index) { return stmts[index].get(); }
};

} // namespace quirk::ast