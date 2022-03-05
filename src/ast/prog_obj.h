#pragma once
#include <memory>
#include <string>
#include <vector>

namespace quirk::ast {

using std::make_unique;
using std::move;
using std::string;
using std::string_view;
using std::unique_ptr;
using std::vector;

class Visitor;

class ProgObj {
    static uint64_t last_id;
    uint64_t id;

public:
    ProgObj() : id(last_id++) {}
    virtual ~ProgObj() {}

    virtual void accept(Visitor* visitor) = 0;

    auto get_id() { return id; }
};

class Expr : public ProgObj {};
class Stmt : public ProgObj {};
class Decl : public ProgObj {};

struct Context {
    size_t line;
    size_t column;
    string_view value;
};

}  // namespace quirk::ast