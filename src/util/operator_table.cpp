#include "operator_table.h"

namespace quirk {

OperatorTable::OperatorTable()
{
    auto i64 = scopes::BasicTypeKind::Int;
    auto f64 = scopes::BasicTypeKind::Float;

    binary_ops[{ast::BinaryOpKind::Add, i64, i64}] = {.result_type = i64};
    binary_ops[{ast::BinaryOpKind::Add, i64, f64}] = {.convert_left_to = f64, .result_type = f64};
    binary_ops[{ast::BinaryOpKind::Add, f64, i64}] = {.convert_right_to = f64, .result_type = f64};
    binary_ops[{ast::BinaryOpKind::Add, f64, f64}] = {.result_type = f64};
}

void OperatorTable::fill_scope(scopes::Scope& scope)
{
    {
        auto i64 = std::make_unique<scopes::BasicType>(scopes::BasicTypeKind::Int);
        scope.insert(move(i64));

        auto f64 = std::make_unique<scopes::BasicType>(scopes::BasicTypeKind::Float);
        scope.insert(move(f64));
    }

    // for (auto [k, v] : binary_ops) {
    //     switch (k.kind) {
    //     case ast::BinaryOpKind::Add:
    //         auto op_add = std::make_unique<scopes::BasicType>(
    //         scope.insert(
    //         break;
    //     default:
    //         throw std::logic_error("Not implemented");
    //     }
    // }
}

const BinaryOpInfo* OperatorTable::find(ast::BinaryOpKind kind, scopes::BasicTypeKind left_type,
                                        scopes::BasicTypeKind right_type)
{
    auto result = binary_ops.find({kind, left_type, right_type});
    if (result != binary_ops.end()) {
        return &result->second;
    }
    return nullptr;
}

const UnaryOpInfo* OperatorTable::find(ast::UnaryOpKind kind, scopes::BasicTypeKind arg_type)
{
    auto result = unary_ops.find({kind, arg_type});
    if (result != unary_ops.end()) {
        return &result->second;
    }
    return nullptr;
}

} // namespace quirk