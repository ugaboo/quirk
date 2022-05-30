#pragma once

#include <string>

namespace quirk {

struct Context {
    size_t line = 0;
    size_t column = 0;
    std::string_view value;
};

} // namespace quirk