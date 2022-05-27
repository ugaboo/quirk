#include "visitor.h"

namespace quirk::ast {

void BinaryExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast