#pragma once

#include "node.h"

namespace quirk::ast {

class ContinueStmt : public Stmt {
public:
    ContinueStmt(Context context) : Stmt(context) {}

    void accept(Visitor* visitor) override { visitor->visit(this); }
};

}  // namespace quirk::ast