#include "visitor.h"

namespace quirk::ast {

void AsgStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast