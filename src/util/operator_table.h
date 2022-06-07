#pragma once

#include <optional>
#include <tuple>
#include <unordered_map>

#include "../ast/binary_expr.h"
#include "../ast/unary_expr.h"
#include "../scopes/basic_type.h"
#include "../scopes/scope.h"
#include "hash_combine.h"

namespace quirk::util {

// struct BinaryOpKey {
//     ast::BinaryOpKind kind;
//     scopes::BasicTypeKind left_type;
//     scopes::BasicTypeKind right_type;
// };

// inline bool operator==(const BinaryOpKey& a, const BinaryOpKey& b)
// {
//     return a.kind == b.kind && a.left_type == b.left_type && a.right_type == b.right_type;
// }

// struct BinaryOpHash {
//     size_t operator()(const BinaryOpKey& key) const noexcept
//     {
//         size_t seed = 0;
//         hash_combine(seed, key.kind);
//         hash_combine(seed, key.left_type);
//         hash_combine(seed, key.right_type);
//         return seed;
//     }
// };

struct BinaryOpInfo {
    std::optional<scopes::BasicTypeKind> convert_left_to;
    std::optional<scopes::BasicTypeKind> convert_right_to;
    scopes::BasicTypeKind result_type;
};

// struct UnaryOpKey {
//     ast::UnaryOpKind kind;
//     scopes::BasicTypeKind arg_type;
// };

// inline bool operator==(const UnaryOpKey& a, const UnaryOpKey& b)
// {
//     return a.kind == b.kind && a.arg_type == b.arg_type;
// }

// struct UnaryOpHash {
//     size_t operator()(UnaryOpKey const& key) const noexcept
//     {
//         size_t seed = 0;
//         hash_combine(seed, key.kind);
//         hash_combine(seed, key.arg_type);
//         return seed;
//     }
// };

struct UnaryOpInfo {
    std::optional<scopes::BasicTypeKind> convert_arg_to;
    scopes::BasicTypeKind result_type;
};

class OperatorTable {
    using BinaryOpKey = std::tuple<ast::BinaryOpKind, scopes::Declaration*, scopes::Declaration*>;
    using UnaryOpKey = std::tuple<ast::UnaryOpKind, scopes::Declaration*>;

    std::unordered_map<BinaryOpKey, BinaryOpInfo> binary_ops;
    std::unordered_map<UnaryOpKey, UnaryOpInfo> unary_ops;

    // std::unordered_map<BinaryOpKey, BinaryOpInfo, BinaryOpHash> binary_ops;
    // std::unordered_map<UnaryOpKey, UnaryOpInfo, UnaryOpHash> unary_ops;

public:
    OperatorTable();

    void fill_scope(scopes::Scope& scope);

    const BinaryOpInfo* find(ast::BinaryOpKind kind, scopes::Declaration* left_type,
                             scopes::Declaration* right_type);

    const UnaryOpInfo* find(ast::UnaryOpKind kind, scopes::Declaration* arg_type);
};

} // namespace quirk::util