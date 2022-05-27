#include "visitor.h"

namespace quirk::ast {

void IfStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast