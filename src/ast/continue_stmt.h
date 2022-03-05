#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class ContinueStmt : public Stmt {
public:
    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast