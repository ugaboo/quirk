#pragma once

#include <string>

namespace quirk {

using std::string_view;

struct Context {
    size_t line;
    size_t column;
    string_view value;
};

} // namespace quirk