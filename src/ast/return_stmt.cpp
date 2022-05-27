#include "visitor.h"

namespace quirk::ast {

void ReturnStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast