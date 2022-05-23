#pragma once
#include "field_def.h"
#include "node.h"

namespace quirk::ast {

class Structure;

class StructDefStmt : public Stmt {
    vector<FieldDefPtr> fields;

public:
    StructDefStmt(Context context, vector<FieldDefPtr>& fields) : Stmt(context)
    {
        for (auto& field : fields) {
            StructDefStmt::fields.push_back(move(field));
        }
    }

    auto get_name() { return get_context().value; }
    auto count_fields() { return fields.size(); }
    auto get_field(size_t index) { return fields[index].get(); }

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast