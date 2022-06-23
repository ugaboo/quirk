#pragma once

#include "field_def_stmt.h"

namespace quirk::ast {

class StructDefStmt : public Stmt {
    std::unique_ptr<NameLiteral> name;
    util::PtrList<FieldDefStmt> fields;

public:
    StructDefStmt(Context context, std::unique_ptr<NameLiteral>& name,
                  std::vector<std::unique_ptr<FieldDefStmt>>& fields)
        : Stmt(context), name(move(name)), fields(fields)
    {
    }

    auto get_name() { return name.get(); }
    auto& get_fields() { return fields; }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast