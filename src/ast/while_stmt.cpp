#include "visitor.h"

namespace quirk::ast {

void WhileStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast