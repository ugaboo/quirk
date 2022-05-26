#pragma once
#include "field_def.h"
#include "node.h"

namespace quirk::ast {

class Structure;

class StructDefStmt : public Stmt {
    unique_ptr<NameLiteral> name;
    vector<unique_ptr<FieldDef>> fields;

public:
    StructDefStmt(Context context, unique_ptr<NameLiteral>& name,
                  vector<unique_ptr<FieldDef>>& fields)
        : Stmt(context), name(move(name))
    {
        for (auto& field : fields) {
            StructDefStmt::fields.push_back(move(field));
        }
    }

    auto get_name() { return name.get(); }
    auto count_fields() { return fields.size(); }
    auto get_field(size_t index) { return fields[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast