#pragma once

#include "field_def_stmt.h"

namespace quirk::ast {

class StructDefStmt : public Stmt {
    std::unique_ptr<NameLiteral> name;
    std::vector<std::unique_ptr<FieldDefStmt>> fields;

public:
    StructDefStmt(Context context, std::unique_ptr<NameLiteral>& name,
                  std::vector<std::unique_ptr<FieldDefStmt>>& fields)
        : Stmt(context), name(move(name))
    {
        for (auto& field : fields) {
            StructDefStmt::fields.push_back(move(field));
        }
    }

    auto get_name() { return name.get(); }
    auto count_fields() { return fields.size(); }
    auto get_field(size_t index) { return fields[index].get(); }

    void accept(Visitor* visitor) override;
};

} // namespace quirk::ast