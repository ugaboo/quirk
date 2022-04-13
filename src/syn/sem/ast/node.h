#pragma once
#include <memory>
#include <string>
#include <vector>

namespace quirk {

class Visitor;

namespace ast {

using std::make_unique;
using std::move;
using std::string;
using std::string_view;
using std::unique_ptr;
using std::vector;

class Node {
    uint64_t id;

public:
    Node() {
        static uint64_t last_id = 0;
        id = last_id++;
    }
    virtual ~Node() {}

    auto get_id() { return id; }

    virtual void accept(quirk::Visitor* visitor) = 0;
};

class Expr : public Node {};
class Stmt : public Node {};
class Decl : public Node {};

struct Context {
    size_t line;
    size_t column;
    string_view value;
};

}  // namespace ast
}  // namespace quirk