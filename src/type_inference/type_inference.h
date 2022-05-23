// #pragma once
// #include <assert.h>
// #include <map>
// #include "visitor.h"

// namespace quirk {

// using std::map;

// class TypeInference : public Visitor {
//     ast::Decl* type = nullptr;

// public:
//     TypeInference(ast::Node* node) {
//         node->accept(this);
//         assert(type != nullptr);
//     }

//     auto& get_type() { return type; }

//     void visit(ast::Function* node) override;
//     void visit(ast::Variable* node) override;
//     void visit(ast::Parameter* node) override;
//     void visit(ast::BinaryExpr* node) override;
//     void visit(ast::CallExprStmt* node) override;
//     void visit(ast::NameLiteral* node) override;
//     void visit(ast::IntLiteral* node) override;
//     void visit(ast::ParameterDef* node) override;
//     void visit(ast::Int64Type* node) override;
//     void visit(ast::Float64Type* node) override;
// };

// }  // namespace quirk