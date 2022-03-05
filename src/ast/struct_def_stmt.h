#pragma once
#include "field_def.h"
#include "prog_obj.h"

namespace quirk::ast {

class Structure;

class StructDefStmt : public Stmt {
    Structure* decl = nullptr;

    Context context;
    vector<unique_ptr<FieldDef>> fields;

public:
    StructDefStmt(Context& context, vector<unique_ptr<FieldDef>>& fields) : context(context) {
        for (auto& field : fields) {
            StructDefStmt::fields.push_back(move(field));
        }
    }

    auto get_name() { return context.value; }
    auto get_decl() { return decl; }
    auto set_decl(Structure* decl) { StructDefStmt::decl = decl; }
    auto count_fields() { return fields.size(); }
    auto get_field(size_t index) { return fields[index].get(); }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast