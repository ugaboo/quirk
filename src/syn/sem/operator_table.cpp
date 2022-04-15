#include "operator_table.h"

namespace quirk {

OperatorTable::OperatorTable() {
    auto i64 = BasicType::Kind::Int64;
    auto f64 = BasicType::Kind::Float64;

    binary_ops[{BinaryExpr::Kind::Add, i64, i64}] = {.result_type = i64};
    binary_ops[{BinaryExpr::Kind::Add, i64, f64}] = {.convert_left_to = f64, .result_type = f64};
    binary_ops[{BinaryExpr::Kind::Add, f64, i64}] = {.convert_right_to = f64, .result_type = f64};
    binary_ops[{BinaryExpr::Kind::Add, f64, f64}] = {.result_type = f64};
}

const BinaryOpInfo* OperatorTable::Find(BinaryExpr::Kind kind,
                                        BasicType::Kind  left_type,
                                        BasicType::Kind  right_type) {
    auto result = binary_ops.find({kind, left_type, right_type});
    if (result != binary_ops.end()) {
        return &result->second;
    }
    return nullptr;
}

const UnaryOpInfo* OperatorTable::Find(UnaryExpr::Kind kind, BasicType::Kind arg_type) {
    auto result = unary_ops.find({kind, arg_type});
    if (result != unary_ops.end()) {
        return &result->second;
    }
    return nullptr;
}

}  // namespace quirk