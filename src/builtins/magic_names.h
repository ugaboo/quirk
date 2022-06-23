#pragma once

#include <string>
#include <unordered_map>

#include "../ast/visitor.h"

namespace quirk::builtins {

std::string_view get_magic_name(ast::BinaryOpKind kind)
{
    using Op = ast::BinaryOpKind;

    static std::unordered_map<ast::BinaryOpKind, std::string_view> names = {
        {Op::Add, "__add__"},     {Op::Sub, "__sub__"},          {Op::Mul, "__mul__"},
        {Op::Div, "__truediv__"}, {Op::IntDiv, "__floordiv__"},  {Op::Mod, "__mod__"},
        {Op::Power, "__pow__"},   {Op::LeftShift, "__lshift__"}, {Op::RightShift, "__rshift__"},
        {Op::BitAnd, "__and__"},  {Op::BitOr, "__or__"},         {Op::BitXor, "__xor__"},
    };

    auto it = names.find(kind);
    if (it != names.end()) {
        return it->second;
    }
    return std::string_view();
}

std::string_view get_magic_name(ast::UnaryOpKind kind)
{
    using Op = ast::UnaryOpKind;

    static std::unordered_map<ast::UnaryOpKind, std::string_view> names = {
        {Op::Minus, "__neg__"},
        {Op::Plus, "__pos__"},
        {Op::BitNot, "__invert__"},
    };

    auto it = names.find(kind);
    if (it != names.end()) {
        return it->second;
    }
    return std::string_view();
}

} // namespace quirk::builtins