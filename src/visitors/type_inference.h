#pragma once
#include <assert.h>
#include <map>
#include "ast/visitor.h"

namespace quirk {

using std::map;

class TypeInference : public ast::Visitor {
    ast::Decl* type = nullptr;

public:
    TypeInference(ast::ProgObj* item) {
        item->accept(this);
        assert(type != nullptr);
    }

    auto& get_type() { return type; }

    void visit(ast::Function* item) override;
    void visit(ast::Variable* item) override;
    void visit(ast::Parameter* item) override;
    void visit(ast::BinaryExpr* item) override;
    void visit(ast::CallExprStmt* item) override;
    void visit(ast::NameLiteral* item) override;
    void visit(ast::IntLiteral* item) override;
    void visit(ast::ParameterDef* item) override;
    void visit(ast::Int64Type* item) override;
    void visit(ast::Float64Type* item) override;
};

}  // namespace quirk