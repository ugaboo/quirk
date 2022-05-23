// #pragma once
// #include <optional>
// #include <unordered_map>
// #include "ast/basic_type.h"
// #include "ast/binary_expr.h"
// #include "ast/unary_expr.h"
// #include "util/hash_combine.h"

// namespace quirk {

// using namespace ast;
// using std::optional;
// using std::unordered_map;

// struct BinaryOpKey {
//     BinaryExpr::Kind kind;
//     BasicType::Kind  left_type;
//     BasicType::Kind  right_type;
// };

// inline bool operator==(const BinaryOpKey& a, const BinaryOpKey& b) {
//     return a.kind == b.kind && a.left_type == b.left_type && a.right_type == b.right_type;
// }

// struct BinaryOpHash {
//     size_t operator()(const BinaryOpKey& key) const noexcept {
//         size_t seed = 0;
//         hash_combine(seed, key.kind);
//         hash_combine(seed, key.left_type);
//         hash_combine(seed, key.right_type);
//         return seed;
//     }
// };

// struct BinaryOpInfo {
//     optional<BasicType::Kind> convert_left_to;
//     optional<BasicType::Kind> convert_right_to;
//     BasicType::Kind           result_type;
// };

// struct UnaryOpKey {
//     UnaryExpr::Kind kind;
//     BasicType::Kind arg_type;
// };

// inline bool operator==(const UnaryOpKey& a, const UnaryOpKey& b) {
//     return a.kind == b.kind && a.arg_type == b.arg_type;
// }

// struct UnaryOpHash {
//     size_t operator()(UnaryOpKey const& key) const noexcept {
//         size_t seed = 0;
//         hash_combine(seed, key.kind);
//         hash_combine(seed, key.arg_type);
//         return seed;
//     }
// };

// struct UnaryOpInfo {
//     optional<BasicType::Kind> convert_arg_to;
//     BasicType::Kind           result_type;
// };

// class OperatorTable {
//     unordered_map<BinaryOpKey, BinaryOpInfo, BinaryOpHash> binary_ops;
//     unordered_map<UnaryOpKey, UnaryOpInfo, UnaryOpHash>    unary_ops;

// public:
//     OperatorTable();
//     ~OperatorTable() = default;

//     const BinaryOpInfo* Find(BinaryExpr::Kind kind,
//                              BasicType::Kind  left_type,
//                              BasicType::Kind  right_type);

//     const UnaryOpInfo* Find(UnaryExpr::Kind kind, BasicType::Kind arg_type);
// };

// }  // namespace quirk