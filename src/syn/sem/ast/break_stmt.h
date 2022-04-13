#pragma once
#include "node.h"

namespace quirk::ast {

class BreakStmt : public Stmt {
public:
    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast