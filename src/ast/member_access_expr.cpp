#include "visitor.h"

namespace quirk::ast {

void MemberAccessExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast