#pragma once

#include <string>
#include <unordered_set>

namespace quirk::builtins {

bool is_reserved(std::string_view name)
{
    static std::unordered_set<std::string_view> names = {"Int", "Float"};

    return names.contains(name);
}

} // namespace quirk::builtins