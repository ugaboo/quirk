#include "visitor.h"

namespace quirk::ast {

void BreakStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast