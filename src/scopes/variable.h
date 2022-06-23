#pragma once

#include "../ast/asg_stmt.h"
#include "../ast/name_literal.h"
#include "prog_obj.h"

namespace quirk::scopes {

class Variable : public ProgObj {
public:
    Variable() {}

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes