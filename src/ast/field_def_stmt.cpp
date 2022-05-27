#include "visitor.h"

namespace quirk::ast {

void FieldDefStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast