#include "visitor.h"

namespace quirk::ast {

void UnaryExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast