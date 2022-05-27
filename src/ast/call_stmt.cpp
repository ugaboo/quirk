#include "visitor.h"

namespace quirk::ast {

void CallStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast