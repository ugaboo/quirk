#pragma once

#include <optional>
#include <unordered_map>

#include "../ast/binary_expr.h"
#include "../ast/unary_expr.h"
#include "../scopes/basic_type.h"
#include "../scopes/scope.h"
#include "hash_combine.h"

namespace quirk::util {

struct BinaryOpInfo {
    scopes::BasicTypeKind result_type;
    std::optional<scopes::BasicTypeKind> convert_left_to;
    std::optional<scopes::BasicTypeKind> convert_right_to;
};

struct UnaryOpInfo {
    std::optional<scopes::BasicTypeKind> convert_arg_to;
    scopes::BasicTypeKind result_type;
};

class OperatorTable {
    struct BinaryOpKey {
        ast::BinaryOpKind kind;
        scopes::Declaration* left_type;
        scopes::Declaration* right_type;

        bool operator==(const BinaryOpKey& other) const;

        struct Hash {
            size_t operator()(const BinaryOpKey& key) const noexcept;
        };
    };

    struct UnaryOpKey {
        ast::UnaryOpKind kind;
        scopes::Declaration* arg_type;

        bool operator==(const UnaryOpKey& other) const;

        struct Hash {
            size_t operator()(UnaryOpKey const& key) const noexcept;
        };
    };

    std::unordered_map<BinaryOpKey, BinaryOpInfo, BinaryOpKey::Hash> binary_ops;
    std::unordered_map<UnaryOpKey, UnaryOpInfo, UnaryOpKey::Hash> unary_ops;

public:
    OperatorTable();

    void fill_scope(scopes::Scope& scope);

    const BinaryOpInfo* find(ast::BinaryOpKind kind, scopes::Declaration* left_type,
                             scopes::Declaration* right_type);

    const UnaryOpInfo* find(ast::UnaryOpKind kind, scopes::Declaration* arg_type);
};

} // namespace quirk::util