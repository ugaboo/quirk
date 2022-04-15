#include "syn/sem/operator_table.h"

using namespace quirk;
using namespace quirk::ast;

int main() {
    quirk::OperatorTable table;
    auto res1 = table.Find(BinaryExpr::Kind::Add, BasicType::Kind::Int64, BasicType::Kind::Int64);
    auto res2 = table.Find(BinaryExpr::Kind::Add, BasicType::Kind::Float64, BasicType::Kind::Int64);
    auto res3 = table.Find(BinaryExpr::Kind::Add, BasicType::Kind::Int64, BasicType::Kind::Float64);
    auto res4 = table.Find(BinaryExpr::Kind::Sub, BasicType::Kind::Int64, BasicType::Kind::Int64);

    auto tmp = *res2->convert_right_to;

    return 0;
}