#pragma once

namespace quirk::util {

class IndentGuard {
    int& indent;

public:
    IndentGuard(int& indent) : indent(indent) { indent++; }
    ~IndentGuard() { indent--; }
};

}  // namespace quirk::util
