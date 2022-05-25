#pragma once

#include "node.h"

namespace quirk::ast {

class BreakStmt : public Stmt {
public:
    BreakStmt(Context context) : Stmt(context) {}

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

} // namespace quirk::ast