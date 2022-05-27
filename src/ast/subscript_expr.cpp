#include "visitor.h"

namespace quirk::ast {

void SubscriptExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast