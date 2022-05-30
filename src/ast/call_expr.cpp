#include "visitor.h"

namespace quirk::ast {

void CallExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast