#include "visitor.h"

namespace quirk::ast {

void StructDefStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast