#include "visitor.h"

namespace quirk::ast {

void ContinueStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast