#include "visitor.h"

namespace quirk::ast {

void ParamDefExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast