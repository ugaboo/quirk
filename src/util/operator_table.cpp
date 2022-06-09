#include "operator_table.h"

namespace quirk::util {

bool OperatorTable::BinaryOpKey::operator==(const BinaryOpKey& other) const
{
    return kind == other.kind && left_type == other.left_type && right_type == other.right_type;
}

size_t OperatorTable::BinaryOpKey::Hash::operator()(const BinaryOpKey& key) const noexcept
{
    size_t seed = 0;
    hash_combine(seed, key.kind);
    hash_combine(seed, key.left_type);
    hash_combine(seed, key.right_type);
    return seed;
}

bool OperatorTable::UnaryOpKey::operator==(const UnaryOpKey& other) const
{
    return kind == other.kind && arg_type == other.arg_type;
}

size_t OperatorTable::UnaryOpKey::Hash::operator()(UnaryOpKey const& key) const noexcept
{
    size_t seed = 0;
    hash_combine(seed, key.kind);
    hash_combine(seed, key.arg_type);
    return seed;
}

OperatorTable::OperatorTable()
{
    auto i64 = scopes::BasicTypeKind::Int;
    auto f64 = scopes::BasicTypeKind::Float;

    // binary_ops[{ast::BinaryOpKind::Add, i64, i64}] = {.result_type = i64};
    // binary_ops[{ast::BinaryOpKind::Add, i64, f64}] = {.convert_left_to = f64, .result_type =
    // f64}; binary_ops[{ast::BinaryOpKind::Add, f64, i64}] = {.convert_right_to = f64, .result_type
    // = f64}; binary_ops[{ast::BinaryOpKind::Add, f64, f64}] = {.result_type = f64};
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

const BinaryOpInfo* OperatorTable::find(ast::BinaryOpKind kind, scopes::Declaration* left_type,
                                        scopes::Declaration* right_type)
{
    auto key = BinaryOpKey{.kind = kind, .left_type = left_type, .right_type = right_type};
    auto result = binary_ops.find(key);
    if (result != binary_ops.end()) {
        return &result->second;
    }
    return nullptr;
}

const UnaryOpInfo* OperatorTable::find(ast::UnaryOpKind kind, scopes::Declaration* arg_type)
{
    auto result = unary_ops.find({kind, arg_type});
    if (result != unary_ops.end()) {
        return &result->second;
    }
    return nullptr;
}

} // namespace quirk::util