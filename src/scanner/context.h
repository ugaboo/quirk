#pragma once

#include <string>

namespace quirk {

struct Context {
    size_t line;
    size_t column;
    std::string_view value;
};

} // namespace quirk