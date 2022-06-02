#pragma once

namespace quirk::util {

class IndentGuard {
    uint64_t& indent;
    uint64_t by;

public:
    IndentGuard(uint64_t& indent, uint64_t by = 4) : indent(indent), by(by) { indent += by; }
    ~IndentGuard() { indent -= by; }
};

} // namespace quirk::util
