#pragma once

#include "asg_stmt.h"
#include "binary_expr.h"
#include "bool_literal.h"
#include "break_stmt.h"
#include "call_expr.h"
#include "call_stmt.h"
#include "continue_stmt.h"
#include "field_def.h"
#include "float_literal.h"
#include "func_def_stmt.h"
#include "if_stmt.h"
#include "int_literal.h"
#include "list_literal.h"
#include "member_access_expr.h"
#include "name_literal.h"
#include "none_literal.h"
#include "param_def_expr.h"
#include "return_stmt.h"
#include "struct_def_stmt.h"
#include "subscript_expr.h"
#include "unary_expr.h"
#include "while_stmt.h"

namespace quirk::ast {

class TranslationUnit {
    vector<unique_ptr<Stmt>> stmts;

public:
    TranslationUnit() = delete;
    TranslationUnit(TranslationUnit&) = delete;
    TranslationUnit(TranslationUnit&&) = delete;

    TranslationUnit(vector<unique_ptr<Stmt>>& stmts)
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