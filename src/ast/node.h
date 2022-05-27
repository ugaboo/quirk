#pragma once

#include "../scanner/context.h"

namespace quirk::ast {

class Visitor;

class Node {
    uint64_t id;
    Context context;

public:
    Node() = delete;
    Node(Node&) = delete;
    Node(Node&&) = delete;

    Node(Context context) : context(context)
    {
        static uint64_t last_id = 0;
        id = last_id++;
    }

    virtual ~Node() {}

    auto get_id() { return id; }

    auto get_context() { return context; }

    virtual void accept(Visitor* visitor) = 0;
};

class Expr : public Node {
public:
    Expr(Context context) : Node(context) {}
};

class Stmt : public Node {
public:
    Stmt(Context context) : Node(context) {}
};

} // namespace quirk::ast